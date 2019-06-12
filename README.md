# Library: graphqlcpp
Graphqlcpp is a library to proccess GraphQl requests. <br>
More information about GraphQl and its syntax you can find [here](https://graphql.org/learn/). <br><br>
This software is part of a project in our university. That's why it does not support all features of graphql (yet).

## Simplified workflow 
* Register a GraphQl schema file.
* Register a introspection file to execute queries with [GraphiQL](https://github.com/graphql/graphiql). 
* Register resolver methods which will be called by us if it is requested.
* Execute query.
  * Validate query against the schema file.
  * Call resolver methods to get the requested data.
  * Return requested data in JSON format.
* Requested data will return in JSON format

## Current state of development
Currently our lib does not support all featues of graphQl. Feal free to add some if you want to.

### Supported Features of GraphQL
Operation:
* Operation Type: _Query_
* request _Fields_ with _Arguments_
* request _Arrays_

Schema:
* set a _schema_
* set _fields_ and _scalar types_ (the leaves of the tree)
* add _arguments_ which can be _non-nullable_

### Planed Features: 
* Enable list types on the first level.

### Not supported (yet):
* query types: Mutation and Subscription
* interfaces
* enumeration types
* input types (which are neccessary for mutation)

## Installation
1. Clone the project.
2. Execute the script [build.sh](https://github.com/graphqlcpp-team/graphqlcpp/blob/master/build.sh)
3. In your own project include the library files. You find them in the directory [include](https://github.com/graphqlcpp-team/graphqlcpp/tree/master/include).
4. Now you can use the functions in [GraphqlCppApi.h](https://github.com/graphqlcpp-team/graphqlcpp/blob/master/include/graphqlcpp/GraphqlCppApi.h) file to interact with the lib.

## Add a schema
A schema looks like this:
```graphql
schema {
    query: Query, 
    mutation: Mutation
} 
type Query { 
    user(id: ID!): User
} 
type User { 
    id: ID! 
    name: string!	
    age: Int
}
```
To add the schema call the methode `void setSchema(const char* schema)`. As you see the parameter is of type `char *`. This is because the intern used library libgrahpqlpaser uses `char *`.
<br>The way to call the method:
```cpp
const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";

GraphqlCppApi *api = ApiFactory::createApi();
api->setSchema(schema);
```
## Add resolver methods.
The resolver methods are needed, because this lib needs to call something to get the data. <br>
In the resolver methods you specify where the data come from and how to call them.<br><br>
To add a resolver method call ``void registerResolver(IGraphQlResolver* resolver);``

### The way you add a resolver method
````cpp
api->registerResolver(new UserResolver());

class UserResolver : public graphqlcpp::resolver::IGraphQlResolver {
    private:
        IGraphQlDTO *dtoObject;
    public:

        IGraphQlDTO * getDtoObject() {
            return dtoObject;
        }

        char *getResolverName() override {
            return "user";
        }
        IGraphQlDTO *execute(const std::vector<ResolverArgument *> *resolverArgs) override {
            dtoObject = DataGenerator::createUser();
            return dtoObject;
        }

    };
````
*Important*: 
* You have to inherit from ``graphqlcpp::resolver::IGraphQlResolver``.
* You have to override the getResovlerName method. This will be the name which will be called in the query.
* You have to ovveride the execute method. Here you have to create dtoObjects. In these you can link to your data

### Add DtoObjects
To the above seen readme this is a simplified structur of the DTOObjects.
````cpp

 class DataGenerator {
    public:
        static Customer *createCustomer() {
            Customer *cu = new Customer("Sven Steuermann", 34);
            return cu;
        }
    };

    class Customer : public IGraphQlDTO {
    private:
        char *name;
        int age;
    public:
        Customer(char *name, int age) {
            this->name = name;
            this->age = age;
        }

        MySerializer *serialize(MySerializer *serializer) override {
            serializer->setVal("name", name);
            serializer->setVal("age", age);
            return serializer;
        }
    };
   
````
The method ``createCustomer`` of the class ``DataGenerator`` will be called in the resolver method. Like you can see in the code example of the resolver methods. This will create a Customer, which is a DTOObject.
<br><br>
The class ``Customer`` is a DTOObject and have to inherit from ``IGraphQlDTO``. The member vairbales are requierd and show which data can be accessed (you can orientate yourself by the schema file). In this case the members are set though the constructor. It is also possible to get the data from a databse or something else. <br>
The ``serialized`` method must be overriden. In there just call the ``serializer->setVal`` method with the member variables and a string. This string represent how this member can be accessed from the query.

#### Nesting of DTOObjects
Be aware of: <br>
On one DTOObject you can reference to another DTOObject. This can be seen here:

````
class Address : public IGraphQlDTO {
    .... //Here is code. To make it shorter it has been removed.
    };
    
    class Customer : public IGraphQlDTO {
    private:
        .... //Here is code from example above
        Address *addressFirst;
    public:
        Customer(char *name, int age, Address *addressFirst) {
            .... //Here is code from example above
            this->addressFirst = addressFirst;
        }

        MySerializer *serialize(MySerializer *serializer) override {
            .... //Here is code from example above
            serializer->setVal("age", age);
            return serializer;
        }
    };
````

## Optinal: register introspection schema
This is not required as long you don't want to work with GraphiQL. If you want to use GraphiQL, register a introspection schema with the method ``void setGraphiQlIntrospectionSchema(std::string introspectionSchema);``

* To get the introspection schema you can use an online converter
* The introspection schema will not be part of a validation
* The introspection schema is delivered by the webserver if requested
* It can be used by GraphiQL to generate the docs menu and the autocomplet functionallity

## Execute a query
With the function ``string executeRequest(const char *request);`` a query will be executed. The function returns the requested data in JSON format.<br>
A query could be:

```cpp
const char * query = "query{user(id:1) {name}}";
const char *response = (api->executeRequest(query)).c_str();
```
The response could be:
````json
{
 "data": {
   "user": {
    "name":"Herbert"
    }
   }
 }
````
* The query with its arguments will be validated againt the schema. If the query is not correct an execption will occur.
* The names, as set in the resolver method and the DTOObjects, can be used to requerst the data. 
  * The name of the resolver method is ``user`` which is the first field requested in the query. 
  * The ``name`` is set in the Customer DTOObject.
* The return data is as usual wrapped with ``"data"``. Inside the ``data`` the requested data will be returned in JSON format.

## License
graphqlcpp is licensed under the MIT License. See [LICENSE](https://github.com/graphqlcpp-team/graphqlcpp/blob/master/LICENSE) for details. <br>
Copyright (c) 2015, Amelie Schmidt, Peter Weinberger, Julian Fruth and [Contributors](https://github.com/graphqlcpp-team/graphqlcpp/graphs/contributors)


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
```
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
To add the schema call the methode 'void setSchema(const char* schema)'. As you see the parameter is of type 'char *'. This is because the intern used library libgrahpqlpaser uses 'char *'.
The way to call the method:
```
const char* schema = "schema {query: Query, mutation: Mutation} type Query { user(id: ID!): User} type User { id: ID! name: string!	age: Int}";

GraphqlCppApi *api = ApiFactory::createApi();
api->setSchema(schema);
```
## Add resolver methods.
The resolver methods are needed, because this lib needs to call something to get the data. 


Project structure:
````plantuml
@startuml
[TODO squenzdiagramm]
@enduml

````

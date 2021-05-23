// open Belt;
// type method = [ | `GET | `POST | `PATCH | `DELETE];
// module Xhr = {
//   type xhr;
//   [@bs.new] external make: unit => xhr = "XMLHttpRequest";
//   [@bs.send.pipe: xhr] external open_: (method, string, bool) => unit = "open";
//   [@bs.send.pipe: xhr] external send: Js.Null.t(string) => unit = "send";
//   [@bs.send.pipe: xhr]
//   external setRequestHeader: (string, string) => unit = "setRequestHeader";
//   [@bs.set] external setResponseType: (xhr, string) => unit = "responseType";
//   [@bs.set]
//   external onChange: (xhr, unit => unit) => unit = "onreadystatechange";
//   [@bs.get] external readyState: xhr => int = "readyState";
//   [@bs.get] external status: xhr => int = "status";
//   [@bs.get] external response: xhr => 'a = "response";
// };
// open Helpers;
type entity = string;

let allEntities = ["Apple", "Banana", "All", "Berry"];

// let query = (~id) => {
//   Request.make(~url=Environment.apiUrl ++ "beers/" ++ id, ())
//   ->Future.mapOk(item => fromJs(item[0]));
// };
// Js.log(Belt.Result.Ok(allEntities |> List.keep(String.contain(_, "a"))))
let contain = (target: string, search: string) =>
  Js.Re.(test_(fromString(search), target));

Js.log(allEntities |> List.filter(contain(_, "a")));
//  let x =(Belt.List.filter(contain(allEntities, "text")));
let x = allEntities |> List.filter(contain(_, "text"));
let xtest = text => allEntities |> List.filter(contain(_, text));

// open Belt;
let parseJsonResult: string => Belt.Result.t(list(entity), exn) =
  text => {
    // let x = allEntities |> List.filter(contain(_, text));
    let result =
      Belt.Result.Ok(allEntities |> List.filter(contain(_, text)));

    switch (result) {
    | Belt.Result.Ok(value) => Belt.Result.Ok(value)
    | Belt.Result.Error(value) => Belt.Result.Ok(value)
    | exception exn => Belt.Result.Error(exn)
    };
  };

  let findEntities: string => Future.t(Belt.Result.t(list(entity), Errors.t)) =
  text =>
    Future.make(resolve => {
    // let result =
    //   Belt.Result.Ok(allEntities |> List.filter(contain(_, text)));
      resolve(
        Belt.Result.Ok(allEntities |> List.filter(contain(_, text))),
      );
    });

// let jwkList = json =>
//   switch (Json.Decode.field("keys", Json.Decode.list(jwk), json)) {
//   | value => Belt.Result.Ok(value)
//   | exception exn => Belt.Result.Error(exn)
//   };
let findEntities: string => Future.t(Belt.Result.t(list(entity), Errors.t)) =
 text =>
    Future.make((resolve) => {

      resolve(
        Belt.Result.Ok(allEntities |> List.filter(contain(_, text))),
      );
    });
let allEntities = ["Apple", "Banana", "All", "Berry"];
let make = (~text, ()) => {
  let future =
    Future.make(resolve => {resolve(Belt.Result.Ok(parseJsonResult(text)))});
  future;
};
let x = make(~text="a",())->Future.map(x => {
    Js.log2("incr(future2Counter)",x);

  })

Future.value(make(~text="a",()))->Future.get(value =>Js.log2("incr(future2Counter)",value));

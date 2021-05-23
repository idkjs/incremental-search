let conversion = (converter: 'a => string, acc: string, item: 'a) => {
  acc ++ converter(item) ++ ", ";
};

let stringOfList = (items: list('a), stringify: 'a => string): string => {
  let reducerFcn = conversion(stringify);
  Belt.List.reduce(items, "[", reducerFcn) ++ "]";
};

let orderList = ["Apple", "Banana", "All", "Berry"];

// let onePrice = ((qty: int, size: ShirtSize.t)) : float => {
//   float_of_int(qty) *. ShirtSize.price(size);
// };

// let priceList = Belt.List.map(orderList, onePrice);
// Js.log(stringOfList(priceList, Js.Float.toString));

// let isMedium = ((_, size)): bool => {
//   size === ShirtSize.Medium;
// };
let allEntities = ["Apple", "Banana", "All", "Berry"];
let isMedium = (target: string, search: string) =>
  Js.Re.(test_(fromString(search), target));

let contain = (target: string, search: string) =>
  Js.Re.(test_(fromString(search), target));
let orderList = ["Apple", "Banana", "All", "Berry"];
let mediums = text => Belt.List.keep(orderList, isMedium(text));
Js.log(mediums("a"));
Js.log(allEntities |> List.filter(contain(_, "a")));

type entity = string;

let allEntities = ["Apple", "Banana", "All", "Berry"];
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
Js.log(parseJsonResult("a"));
let findEntities: string => Future.t(Belt.Result.t(list(entity), Errors.t)) =
  text =>
    Future.make(resolve => {
      // let result =
      //   Belt.Result.Ok(allEntities |> List.filter(contain(_, text)));
      Js.log(text);
      resolve(
        Belt.Result.Ok(allEntities |> List.filter(contain(_, text))),
      );
    });

Js.log2(
  "Future.get",
  findEntities("a")->Future.get(payload => Js.log(payload)),
);
let findEntities: string => Future.t(Belt.Result.t(list(entity), Errors.t)) =
  text =>
    Future.make(resolve =>
      Belt.Result.Ok(allEntities |> List.filter(contain(_, text)))->resolve
    );
Js.log2(
  "Future.get",
  findEntities("a")->Future.get(payload => Js.log(payload)),
);
let future = Future.make(resolve => {resolve(parseJsonResult("a"))});
let future2 =
  future->Future.get(x => {
    Js.log("incr(future2Counter)");
    Js.log(x);
  });
let future = Future.make(resolve => {resolve(findEntities("a"))});
let future2 =
  future->Future.get(x => {
    Js.log("incr(future2Counter)");
    Js.log(x);
  });

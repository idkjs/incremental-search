module TextIncrementalSearchDef = {
  open Helpers;
  type entity = string;
  let allEntities = ["Apple", "Banana", "All", "Berry"];
  let findEntities = text =>
    Js.Promise.make((~resolve, ~reject as _) =>
      resolve(. allEntities |> List.filter(String.contain(_, text)))
    );
};
module TextIncrementalSearchDefHooks = {
  open Helpers;
  type entity = string;
  let allEntities = ["Apple", "Banana", "All", "Berry"];
  // let findEntities: string => Future.t(list(string)) =
  //   text =>
  //     Future.make(resolve => {
  //       resolve(allEntities |> List.filter(String.contain(_, text)))
  //     });
  // let future2Counter = ref(0);
  // let futureEntities = ref(allEntities);
  // let future =
  //   Future.make(resolve => {
  //     let timeoutId =
  //       Js.Global.setTimeout(() => resolve(futureEntities), 10);
  //     Some(() => Js.Global.clearTimeout(timeoutId));
  //   });

  let findEntities:
    string => Future.t(Belt.Result.t(list(entity), Errors.t)) =
    text =>
      Future.make(resolve => {
        resolve(
          Belt.Result.Ok(
            allEntities |> List.filter(String.contain(_, text)),
          ),
        )
      });
};

module TextIncrementalSearch =
  IncrementalSearch.IncrementalSearch(TextIncrementalSearchDefHooks);

module TextIncrementalSearchCompat =
  IncrementalSearchCompat.IncrementalSearch(TextIncrementalSearchDef);

ReactDOMRe.renderToElementWithId(
  <div>
    <header role="heading" ariaLevel=1>
      "Incremental Future"->React.string
    </header>
    <TextIncrementalSearch
      searchResultView={results => {
        Js.log(results);
        <ul>
          {results
           |> List.map(text => <li key=text> {text |> React.string} </li>)
           |> Array.of_list
           |> React.array}
        </ul>;
      }}
    />
    <header role="heading" ariaLevel=1>
      "Incremental Compat"->React.string
    </header>
    <TextIncrementalSearchCompat
      searchResultView={results =>
        <ul>
          {results
           |> List.map(text => <li key=text> {text |> React.string} </li>)
           |> Array.of_list
           |> React.array}
        </ul>
      }
    />
  </div>,
  "index",
);



open Helpers;

module type Def = {
  type entity;
  // let findEntities: string => RequestStatus.t(Belt.Result.t(list(entity),Errors.t));
  let findEntities:
    string => Future.t(Belt.Result.t(list(entity), Errors.t));
};

module IncrementalSearch = (D: Def) => {

  type state = {
    text: string,
    entities: RequestStatus.t(Belt.Result.t(list(D.entity), Errors.t)),
    queueGetEntitesCommand: list(string),
  };
  type action =
    | LoadEntityList
    | InputText(string)
    | CompletedFindEntities(Belt.Result.t(list(D.entity), Errors.t))
    | Dequeue(state);
  [@react.component]
  let make =
      (
        ~defaultText: option(string)=?,
        ~searchDelay: option(float)=?,
        ~searchResultView: list(D.entity) => React.element,
        (),
      ) => {
    let (state, dispatch) =
      React.useReducer(
        (state, action) =>
          switch (action) {
          | LoadEntityList => {...state, entities: Loading}
          | CompletedFindEntities(entities) => {
              ...state,
              entities: Done(entities),
            }
          | InputText(text) => {
              ...state,
              text,
              queueGetEntitesCommand:
                List.concat([state.queueGetEntitesCommand, [text]]),
            }
          | Dequeue(state) => state
          },
        {
          text: Option.withDefault("", defaultText),
          entities: NotAsked,
          queueGetEntitesCommand: [],
        },
      );

    let dequeue = () => {
      let state =
        switch (state.queueGetEntitesCommand) {
        | [command] =>
          D.findEntities(command)
          ->Future.get(entities => {
              Js.log2("handleCommand entities", entities);
              dispatch(CompletedFindEntities(entities));
            });
          {...state, queueGetEntitesCommand: []};
        | [_, ...tail] => {...state, queueGetEntitesCommand: tail}
        | [] => state
        };
      // state;
      dispatch(Dequeue(state));
    };
    let delay = Option.withDefault(0.0, searchDelay);
    let text = state.text;
    let onInputText = e => {
      let text = ReactEvent.Form.target(e)##value;
      dispatch(InputText(text));
      let _ =
        Js.Global.setTimeout(() => dequeue(), delay |> floor |> int_of_float);
      ();
    };
  // let loadEntitiesList = () => {
  //   EntitiesList.query()
  //   ->Future.get(payload => dispatch(ReceiveEntitiesList(payload)));
  // };
  // React.useEffect0(() => {
  //   loadEntitiesList();
  //   None;
  // });
  // let Belt.Result.(entities) = (state.entities)->Future.mapOk;
  // let entities = Belt.Result.(state.entities)->Future.mapOk;
    <div>
      <input onInput={e => onInputText(e)} value=text />
  //  {searchResultView(entities)}
      {switch (state.entities) {
       | NotAsked => React.string("Not Asked")
       | Loading => React.string("Loading")
       | Done(Error(_)) => React.string("Request failed")
       | Done(Ok(entities)) => searchResultView(entities)
       }}
    </div>;
  };
};

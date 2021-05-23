  open Belt;
  let fromOptional = optional =>
    optional->Option.mapWithDefault(
      Future.make(r => (400, "")->Result.Error->r), value =>
      Future.make(r => value->Result.Ok->r)
    );

  let fromNullable = nullable => nullable->Js.Nullable.toOption->fromOptional;

  let toError = data => Future.make(r => data->Error->r);

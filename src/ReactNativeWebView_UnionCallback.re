module Make = (T: {
                 type union;
                 type navigationEvent;
                 type errorEvent;
               }) => {
  type t = ReactNative.Event.syntheticEvent(T.union) => unit;

  [@bs.get] external description: T.union => option(string) = "description";
  external convert: ('a => unit) => t = "%identity";
  let make =
      (
        ~navigationCallback: T.navigationEvent => unit,
        ~errorCallback: T.errorEvent => unit,
      )
      : t => {
    x =>
      switch (description(x##nativeEvent)) {
      | None => convert(navigationCallback, x)
      | Some(_) => convert(errorCallback, x)
      };
  };
};

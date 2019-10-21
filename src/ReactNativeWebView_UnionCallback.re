module Make = (T: {
                 type union;
                 type navigationEvent;
                 type errorEvent;
               }) => {
  type t = ReactNative.Event.syntheticEvent(T.union) => unit;

  [@bs.get] external description: T.union => option(string) = "description";
  external convert: ReactNative.Event.syntheticEvent(T.union) => 'a =
    "%identity";
  let make =
      (
        ~navigationCallback: T.navigationEvent => unit,
        ~errorCallback: T.errorEvent => unit,
      )
      : t => {
    x =>
      switch (description(x##nativeEvent)) {
      | None => navigationCallback(convert(x))
      | Some(_) => errorCallback(convert(x))
      };
  };

  let uncurriedMake =
      (
        ~navigationCallback: (. T.navigationEvent) => unit,
        ~errorCallback: (. T.errorEvent) => unit,
      )
      : t => {
    x =>
      switch (description(x##nativeEvent)) {
      | None => navigationCallback(. convert(x))
      | Some(_) => errorCallback(. convert(x))
      };
  };
};

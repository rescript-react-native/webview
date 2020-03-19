module Make = (T: {type t;}) => {
  [@bs.send] external clearFormData: T.t => unit = "clearFormData";
  [@bs.send] external clearCache: T.t => unit = "clearCache";
  [@bs.send] external clearHistory: T.t => unit = "clearHistory";
  [@bs.send] external requestFocus: T.t => unit = "requestFocus";
  [@bs.send] external goForward: T.t => unit = "goForward";
  [@bs.send] external goBack: T.t => unit = "goBack";
  [@bs.send] external reload: T.t => unit = "reload";
  [@bs.send] external stopLoading: T.t => unit = "stopLoading";
  [@bs.send]
  external injectJavaScript: (T.t, string) => unit = "injectJavaScript";
};

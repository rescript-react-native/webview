type element;
type ref = React.Ref.t(Js.nullable(element));

include ReactNativeWebView_Methods.Make({
  type t = element;
});

include ReactNative.NativeMethods.Make({
  type t = element;
});

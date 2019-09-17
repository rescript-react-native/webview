include ReactNativeWebView_Element;

module Source = {
  type t;

  [@bs.obj]
  external uri:
    (
      ~uri: string=?,
      ~method: [@bs.string] [
                 | `CONNECT
                 | `DELETE
                 | `GET
                 | `HEAD
                 | `OPTIONS
                 | `PATCH
                 | `POST
                 | `PUT
                 | `TRACE
               ]
                 =?,
      ~headers: Js.t('a)=?,
      ~body: string=?,
      unit
    ) =>
    t =
    "";

  [@bs.obj]
  external html: (~html: string=?, ~baseUrl: string=?, unit) => t = "";
};

module DataDetectorTypes = ReactNativeWebView_DataDetectorTypes;
module DecelerationRate = ReactNativeWebView_DecelerationRate;
module NavigationType = ReactNativeWebView_NavigationType;

class type webViewNativeEvent = {
  pub target: ReactNative.NativeTypes.nodeHandle;
  pub url: string;
  pub title: string;
  pub loading: bool;
  pub canGoBack: bool;
  pub canGoForward: bool;
  pub lockIdentifier: int;
};

class type virtual webViewError = {
  as 'self;
  constraint 'self = #webViewNativeEvent;
  pub description: string;
  pub domain: option(string);
  pub code: int;
  pub didFailProvisionalNavigation: option(bool);
};

class type virtual webViewMessage = {
  as 'self;
  constraint 'self = #webViewNativeEvent;
  pub data: string;
};

class type virtual webViewNativeProgressEvent = {
  as 'self;
  constraint 'self = #webViewNativeEvent;
  pub progress: float;
};

class type virtual webViewNavigation = {
  as 'self;
  constraint 'self = #webViewNativeEvent;
  pub navigationType: ReactNativeWebView_NavigationType.t;
  pub mainDocumentURL: option(string);
};

type webViewNavigationOrError;

type webViewErrorEvent =
  ReactNative.Event.syntheticEvent(Js.t(webViewError));
type webViewMessageEvent =
  ReactNative.Event.syntheticEvent(Js.t(webViewMessage));
type webViewNavigationEvent =
  ReactNative.Event.syntheticEvent(Js.t(webViewNavigation));
type webViewProgressEvent =
  ReactNative.Event.syntheticEvent(Js.t(webViewNativeProgressEvent));

module UnionCallback =
  ReactNativeWebView_UnionCallback.Make({
    type union = Js.t(webViewNavigationOrError);
    type navigationEvent = webViewNavigationEvent;
    type errorEvent = webViewErrorEvent;
  });

type nativeConfig;

[@bs.obj]
external nativeConfig:
  (~component: React.component('a)=?, ~props: Js.t('b)=?, ~viewManager: Js.t('c)=?) =>
  nativeConfig =
  "";

type request = {
  .
  "url": string,
  "title": string,
  "loading": bool,
  "canGoBack": bool,
  "canGoForward": bool,
  "lockIdentifier": string,
  "navigationType": ReactNativeWebView_NavigationType.t,
};

[@react.component] [@bs.module "react-native-webview"]
external make:
  (
    ~ref: ref=?,
    // WebView props
    ~allowingReadAccessToURL: string=?,
    ~allowFileAccess: bool=?,
    ~allowUniversalAccessFromFileURLs: bool=?,
    ~allowsBackForwardNavigationGestures: bool=?,
    ~allowsFullscreenVideo: bool=?,
    ~allowsInlineMediaPlayback: bool=?,
    ~allowsLinkPreview: bool=?,
    ~androidHardwareAccelerationDisabled: bool=?,
    ~applicationNameForUserAgent: bool=?,
    ~automaticallyAdjustContentInsets: bool=?,
    ~bounces: bool=?,
    ~cacheEnabled: bool=?,
    ~contentInset: ReactNative.View.edgeInsets=?,
    ~contentInsetAdjustmentBehavior: [@bs.string] [
                                       | `never
                                       | `always
                                       | `automatic
                                       | `scrollableAxes
                                     ]
                                       =?,
    ~dataDetectorTypes: array(DataDetectorTypes.t)=?,
    ~decelerationRate: DecelerationRate.t=?,
    ~directionalLockEnabled: bool=?,
    ~domStorageEnabled: bool=?,
    ~geolocationEnabled: bool=?,
    ~hideKeyboardAccessoryView: bool=?,
    ~incognito: bool=?,
    ~injectedJavaScript: string=?,
    ~javaScriptEnabled: bool=?,
    ~keyboardDisplayRequiresUserAction: bool=?,
    ~mediaPlaybackRequiresUserAction: bool=?,
    ~mixedContentMode: [@bs.string] [ | `never | `always | `compatibility]=?,
    ~nativeConfig: nativeConfig=?,
    ~onError: webViewErrorEvent => unit=?,
    ~onLoad: webViewNavigationEvent => unit=?,
    ~onLoadEnd: UnionCallback.t=?,
    ~onLoadStart: webViewNavigationEvent => unit=?,
    ~onMessage: webViewMessageEvent => unit=?,
    ~onLoadProgress: webViewProgressEvent => unit=?,
    ~onNavigationStateChange: Js.t(webViewNavigation) => unit=?,
    ~onShouldStartLoadWithRequest: request => bool=?,
    ~originWhitelist: array(string)=?,
    ~overScrollMode: [@bs.string] [ | `never | `always | `content]=?,
    ~pagingEnabled: bool=?,
    ~renderError: string => React.element=?,
    ~renderLoading: unit => React.element=?,
    ~saveFormDataDisabled: bool=?,
    ~scalesPageToFit: bool=?,
    ~scrollEnabled: bool=?,
    ~sharedCookiesEnabled: bool=?,
    ~showsHorizontalScrollIndicator: bool=?,
    ~showsVerticalScrollIndicator: bool=?,
    ~source: Source.t=?,
    ~startInLoadingState: bool=?,
    ~textZoom: float=?,
    ~thirdPartyCookiesEnabled: bool=?,
    ~userAgent: string=?,
    // View props
    ~accessibilityComponentType: [@bs.string] [
                                   | `none
                                   | `button
                                   | `radiobutton_checked
                                   | `radiobutton_unchecked
                                 ]
                                   =?,
    ~accessibilityElementsHidden: bool=?,
    ~accessibilityHint: string=?,
    ~accessibilityIgnoresInvertColors: bool=?,
    ~accessibilityLabel: string=?,
    ~accessibilityLiveRegion: [@bs.string] [ | `none | `polite | `assertive]=?,
    ~accessibilityRole: [@bs.string] [
                          | `none
                          | `button
                          | `link
                          | `search
                          | `image
                          | `keyboardkey
                          | `text
                          | `adjustable
                          | `header
                          | `summary
                          | `imagebutton
                        ]
                          =?,
    ~accessibilityStates: array(ReactNative.AccessibilityState.t)=?,
    ~accessibilityTraits: array(ReactNative.AccessibilityTrait.t)=?,
    ~accessibilityViewIsModal: bool=?,
    ~accessible: bool=?,
    ~collapsable: bool=?,
    ~hitSlop: ReactNative.View.edgeInsets=?,
    ~importantForAccessibility: [@bs.string] [
                                  | `auto
                                  | `yes
                                  | `no
                                  | [@bs.as "no-hide-descendants"]
                                    `noHideDescendants
                                ]
                                  =?,
    ~nativeID: string=?,
    ~needsOffscreenAlphaCompositing: bool=?,
    ~onAccessibilityEscape: unit => unit=?,
    ~onAccessibilityTap: unit => unit=?,
    ~onLayout: ReactNative.Event.layoutEvent => unit=?,
    ~onMagicTap: unit => unit=?,
    // Gesture Responder props
    ~onMoveShouldSetResponder: ReactNative.Event.pressEvent => bool=?,
    ~onMoveShouldSetResponderCapture: ReactNative.Event.pressEvent => bool=?,
    ~onResponderEnd: ReactNative.Event.pressEvent => unit=?,
    ~onResponderGrant: ReactNative.Event.pressEvent => unit=?,
    ~onResponderMove: ReactNative.Event.pressEvent => unit=?,
    ~onResponderReject: ReactNative.Event.pressEvent => unit=?,
    ~onResponderRelease: ReactNative.Event.pressEvent => unit=?,
    ~onResponderStart: ReactNative.Event.pressEvent => unit=?,
    ~onResponderTerminate: ReactNative.Event.pressEvent => unit=?,
    ~onResponderTerminationRequest: ReactNative.Event.pressEvent => bool=?,
    ~onStartShouldSetResponder: ReactNative.Event.pressEvent => bool=?,
    ~onStartShouldSetResponderCapture: ReactNative.Event.pressEvent => bool=?,
    ~pointerEvents: [@bs.string] [
                      | `auto
                      | `none
                      | [@bs.as "box-none"] `boxNone
                      | [@bs.as "box-only"] `boxOnly
                    ]
                      =?,
    ~removeClippedSubviews: bool=?,
    ~renderToHardwareTextureAndroid: bool=?,
    ~shouldRasterizeIOS: bool=?,
    ~style: ReactNative.Style.t=?,
    ~testID: string=?
  ) =>
  React.element =
  "default";

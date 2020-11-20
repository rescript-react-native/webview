open ReactNative;
include NativeElement;

module Source = {
  type t;

  [@bs.obj]
  external uri:
    (
      ~uri: string=?,
      ~method: [
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
    t;

  [@bs.obj] external html: (~html: string=?, ~baseUrl: string=?, unit) => t;
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
};

class type virtual webViewError = {
  as 'self;
  constraint 'self = #webViewNativeEvent;
  pub description: string;
  pub domain: option(string);
  pub code: int;
  pub didFailProvisionalNavigation: option(bool);
};

class type virtual webViewHttpError = {
  as 'self;
  constraint 'self = #webViewNativeEvent;
  pub description: string;
  pub statusCode: int;
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

class type virtual webViewShouldStartLoadWithRequest = {
  as 'self;
  constraint 'self = #webViewNativeEvent;
  pub navigationType: ReactNativeWebView_NavigationType.t;
  pub mainDocumentURL: option(string);
  pub lockIdentifier: int;
  pub isTopFrame: bool;
};

type webViewNavigationOrError;

module WebViewDownloadEvent = {
  type payload = {downloadUrl: string};

  include Event.SyntheticEvent({
    type _payload = payload;
  });
};

module WebViewErrorEvent = {
  type payload = Js.t(webViewError);
  include Event.SyntheticEvent({
    type _payload = payload;
  });
};
module WebViewHttpErrorEvent = {
  type payload = Js.t(webViewHttpError);
  include Event.SyntheticEvent({
    type _payload = payload;
  });
};
module WebViewMessageEvent = {
  type payload = Js.t(webViewMessage);
  include Event.SyntheticEvent({
    type _payload = payload;
  });
};
module WebViewNavigationEvent = {
  type payload = Js.t(webViewNavigation);
  include Event.SyntheticEvent({
    type _payload = payload;
  });
};
module WebViewProgressEvent = {
  type payload = Js.t(webViewNativeProgressEvent);
  include Event.SyntheticEvent({
    type _payload = payload;
  });
};
module WebViewRenderProcessGone = {
  type payload = {didCrash: bool};
  include Event.SyntheticEvent({
    type _payload = payload;
  });
};
module WebViewTerminatedEvent = {
  type payload = Js.t(webViewNativeEvent);
  include Event.SyntheticEvent({
    type _payload = payload;
  });
};

module UnionCallback =
  ReactNativeWebView_UnionCallback.Make({
    type union = Js.t(webViewNavigationOrError);
    type navigationEvent = WebViewNavigationEvent.t;
    type errorEvent = WebViewErrorEvent.t;
  });

type nativeConfig;

[@bs.obj]
external nativeConfig:
  (
    ~component: React.component('a)=?,
    ~props: Js.t('b)=?,
    ~viewManager: Js.t('c)=?
  ) =>
  nativeConfig;

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
    ~applicationNameForUserAgent: string=?,
    ~automaticallyAdjustContentInsets: bool=?,
    ~bounces: bool=?,
    ~cacheEnabled: bool=?,
    ~cacheMode: [@bs.string] [
                  | [@bs.as "LOAD_DEFAULT"] `default
                  | [@bs.as "LOAD_CACHE_ONLY"] `cacheOnly
                  | [@bs.as "LOAD_CACHE_ELSE_NETWORK"] `cacheElseNetwork
                  | [@bs.as "LOAD_NO_CACHE"] `noCache
                ]
                  =?,
    ~containerStyle: ReactNative.Style.t=?,
    ~contentInset: ReactNative.View.edgeInsets=?,
    ~contentInsetAdjustmentBehavior: [
                                       | `never
                                       | `always
                                       | `automatic
                                       | `scrollableAxes
                                     ]
                                       =?,
    ~contentMode: [ | `recommended | `mobile | `desktop]=?,
    ~dataDetectorTypes: array(DataDetectorTypes.t)=?,
    ~decelerationRate: DecelerationRate.t=?,
    ~directionalLockEnabled: bool=?,
    ~domStorageEnabled: bool=?,
    ~geolocationEnabled: bool=?,
    ~hideKeyboardAccessoryView: bool=?,
    ~incognito: bool=?,
    ~injectedJavaScript: string=?,
    ~injectedJavaScriptForMainFrameOnly: bool=?,
    ~injectedJavaScriptBeforeContentLoaded: string=?,
    ~injectedJavaScriptBeforeContentLoadedForMainFrameOnly: bool=?,
    ~javaScriptCanOpenWindowsAutomatically: bool=?,
    ~javaScriptEnabled: bool=?,
    ~keyboardDisplayRequiresUserAction: bool=?,
    ~mediaPlaybackRequiresUserAction: bool=?,
    ~mixedContentMode: [ | `never | `always | `compatibility]=?,
    ~nativeConfig: nativeConfig=?,
    ~onContentProcessDidTerminate: WebViewTerminatedEvent.t => unit=?,
    ~onFileDownload: WebViewDownloadEvent.t => unit=?,
    ~onError: WebViewErrorEvent.t => unit=?,
    ~onHttpError: WebViewHttpErrorEvent.t => unit=?,
    ~onLoad: WebViewNavigationEvent.t => unit=?,
    ~onLoadEnd: UnionCallback.t=?,
    ~onLoadProgress: WebViewProgressEvent.t => unit=?,
    ~onLoadStart: WebViewNavigationEvent.t => unit=?,
    ~onMessage: WebViewMessageEvent.t => unit=?,
    ~onNavigationStateChange: Js.t(webViewNavigation) => unit=?,
    ~onRenderProcessGone: WebViewRenderProcessGone.t => unit=?,
    ~onShouldStartLoadWithRequest: Js.t(webViewShouldStartLoadWithRequest) =>
                                   bool
                                     =?,
    ~originWhitelist: array(string)=?,
    ~overScrollMode: [ | `never | `always | `content]=?,
    ~pagingEnabled: bool=?,
    ~pullToRefreshEnabled: bool=?,
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
    ~ignoreSilentHardwareSwitch: bool=?,
    ~thirdPartyCookiesEnabled: bool=?,
    ~userAgent: string=?,
    // View props 0.63.0
    ~accessibilityActions: array(Accessibility.actionInfo)=?,
    ~accessibilityElementsHidden: bool=?,
    ~accessibilityHint: string=?,
    ~accessibilityIgnoresInvertColors: bool=?,
    ~accessibilityLabel: string=?,
    ~accessibilityLiveRegion: Accessibility.liveRegion=?,
    ~accessibilityRole: Accessibility.role=?,
    ~accessibilityState: Accessibility.state=?,
    ~accessibilityValue: Accessibility.value=?,
    ~accessibilityViewIsModal: bool=?,
    ~accessible: bool=?,
    ~collapsable: bool=?,
    ~hitSlop: View.edgeInsets=?,
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
    ~onAccessibilityAction: Accessibility.actionEvent => unit=?,
    ~onAccessibilityEscape: unit => unit=?,
    ~onAccessibilityTap: unit => unit=?,
    ~onLayout: Event.layoutEvent => unit=?,
    ~onMagicTap: unit => unit=?,
    // Gesture Responder props
    ~onMoveShouldSetResponder: Event.pressEvent => bool=?,
    ~onMoveShouldSetResponderCapture: Event.pressEvent => bool=?,
    ~onResponderEnd: Event.pressEvent => unit=?,
    ~onResponderGrant: Event.pressEvent => unit=?,
    ~onResponderMove: Event.pressEvent => unit=?,
    ~onResponderReject: Event.pressEvent => unit=?,
    ~onResponderRelease: Event.pressEvent => unit=?,
    ~onResponderStart: Event.pressEvent => unit=?,
    ~onResponderTerminate: Event.pressEvent => unit=?,
    ~onResponderTerminationRequest: Event.pressEvent => bool=?,
    ~onStartShouldSetResponder: Event.pressEvent => bool=?,
    ~onStartShouldSetResponderCapture: Event.pressEvent => bool=?,
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
    ~style: Style.t=?,
    ~testID: string=?,
    ~children: React.element=?,
    // React Native Web Props
    ~onMouseDown: ReactEvent.Mouse.t => unit=?,
    ~onMouseEnter: ReactEvent.Mouse.t => unit=?,
    ~onMouseLeave: ReactEvent.Mouse.t => unit=?,
    ~onMouseMove: ReactEvent.Mouse.t => unit=?,
    ~onMouseOver: ReactEvent.Mouse.t => unit=?,
    ~onMouseOut: ReactEvent.Mouse.t => unit=?,
    ~onMouseUp: ReactEvent.Mouse.t => unit=?
  ) =>
  React.element =
  "default";

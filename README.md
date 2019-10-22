---

# `@reason-react-native/webview`

[![Build Status](https://github.com/reason-react-native/webview/workflows/Build/badge.svg)](https://github.com/reason-react-native/webview/actions)
[![Version](https://img.shields.io/npm/v/@reason-react-native/webview.svg)](https://www.npmjs.com/@reason-react-native/webview)
[![Chat](https://img.shields.io/discord/235176658175262720.svg?logo=discord&colorb=blue)](https://reasonml-community.github.io/reason-react-native/discord/)

[ReasonML](https://reasonml.github.io) /
[BuckleScript](https://bucklescript.github.io) bindings for
[`react-native-webview`](https://github.com/react-native-community/react-native-webview).

Exposed as the `ReactNativeWebView` module.

Version x.y.z of `@reason-react-native/webview` is intended to be compatible with version x.y.* of `@react-native-community/react-native-webview`.

## Installation

When
[`react-native-webview`](`https://github.com/react-native-community/react-native-webview`)
is properly installed & configured by following their installation instructions,
you can install the bindings:

```console
npm install @reason-react-native/webview
# or
yarn add @reason-react-native/webview
```

`@reason-react-native/webview` should be added to `bs-dependencies` in your
`bsconfig.json`. For example,

```diff
{
  //...
  "bs-dependencies": [
    "reason-react",
    "reason-react-native",
    // ...
+    "@reason-react-native/webview"
  ],
  //...
}
```

## Usage

### Types

#### `DataDetectorTypes.t`

Valid values are:

• `DataDetectorTypes.phoneNumber`
• `DataDetectorTypes.link`
• `DataDetectorTypes.address`
• `DataDetectorTypes.calendarEvent`
• `DataDetectorTypes.none`
• `DataDetectorTypes.all`
• `DataDetectorTypes.trackingNumber`
• `DataDetectorTypes.flightNumber`
• `DataDetectorTypes.lookupSuggestion`

#### `DecelerationRate.t`

Values may be created using `DecelerationRate.value`

```reason
value: float => t
```

Other valid values are `DecelerationRate.normal` and `DecelerationRate.fast` which are equivalent to specifying `0.998` and `0.99` and match the underlying iOS settings for `UIScrollViewDecelerationRateNormal` and `UIScrollViewDecelerationRateFast` respectively. 

normal: 0.998
fast: `0.99` (the default for iOS web view)

#### `NavigationType.t`

Valid values are:

• `NavigationType.click`
• `NavigationType.formsubmit`
• `NavigationType.backforward`
• `NavigationType.reload`
• `NavigationType.formresubmit`
• `NavigationType.other`

#### `Source.t`

##### URI

```reason
uri:
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
    t
```

- `uri` specifies the URI (local or remote) to load in the WebView.
- `method` specifies HTTP Method to use, defaults to `` `GET``. Only `` `GET`` and `` `POST`` are supported on Android.
- `headers` specifies additional HTTP headers to send with the request. This can only be used with `` `GET`` requests on Android.
- `body` specifies HTTP body to send with the request. This must be a valid UTF-8 string, and will be sent exactly as specified, with no additional encoding (e.g. URL-escaping or base64) applied. This can only be used with `` `POST`` requests on Android.

##### Static HTML



```reason
html: (~html: string=?, ~baseUrl: string=?, unit) => t 
```

#### `UnionCallback.t`

Type of function passed to the [`onLoadEnd`](#onloadend-unioncallbackt) prop, to handle the union type [`webViewNavigationOrError`](#webviewnavigationorerror). Defined as

```reason
ReactNative.Event.syntheticEvent(Js.t(webViewNavigationOrError)) => unit
```

##### `UnionCallback.make`

Creates a function of type `UnionCallback.t`

```reason
make:
  (
    ~navigationCallback: webViewNavigationEvent => unit,
    ~errorCallback: webViewErrorEvent => unit
  ) =>
  t;
```

##### `UnionCallback.uncurriedMake`

Creates a function of type `UnionCallback.t`

```reason
uncurriedMake:
  (
    ~navigationCallback:(. webViewNavigationEvent) => unit,
    ~errorCallback:(. webViewErrorEvent) => unit
  ) =>
  t;
```


#### `element`

Represents a `WebView` instance, to be used with [methods](#methods).

#### `nativeConfig`

Should be constructed as below:

```reason
nativeConfig:
  (
    ~component: React.component('a)=?,
    ~props: Js.t('b)=?,
    ~viewManager: Js.t('c)=?
  ) =>
  nativeConfig
```

You may refer to [iOS-](https://github.com/react-native-community/react-native-webview/blob/master/docs/Custom-iOS.md) and [Android-](https://github.com/react-native-community/react-native-webview/blob/master/docs/Custom-Android.md)specific guides on how to create a custom `WebView`.

#### `ref`

React `ref` intended to access a `WebView` instance. Defined as

```reason
type ref = React.Ref.t(Js.nullable(element))
```

#### `webViewNativeEvent`

Has the below keys, which can be accessed with `##`.

* `target: ReactNative.NativeTypes.nodeHandle`
* `url: string`
* `title: string`
* `loading: bool`
* `canGoBack: bool`
* `canGoForward: bool`

#### `webViewError`

Has the below keys, which can be accessed with `##`.

* `target: ReactNative.NativeTypes.nodeHandle`
* `url: string`
* `title: string`
* `loading: bool`
* `canGoBack: bool`
* `canGoForward: bool`
* `description: string`
* `domain: option(string)`
* `code: int`
* `didFailProvisionalNavigation: option(bool)`

Note: `domain` key only exists on iOS

#### `webViewHttpError`

Has the below keys, which can be accessed with `##`.

* `target: ReactNative.NativeTypes.nodeHandle`
* `url: string`
* `title: string`
* `loading: bool`
* `canGoBack: bool`
* `canGoForward: bool`
* `description: string`
* `statusCode: int`

Note: `description` key only exists on iOS

#### `webViewMessage`

Has the below keys, which can be accessed with `##`.

* `target: ReactNative.NativeTypes.nodeHandle`
* `url: string`
* `title: string`
* `loading: bool`
* `canGoBack: bool`
* `canGoForward: bool`
* `data: string`


#### `webViewNativeProgressEvent`

Has the below keys, which can be accessed with `##`.

* `target: ReactNative.NativeTypes.nodeHandle`
* `url: string`
* `title: string`
* `loading: bool`
* `canGoBack: bool`
* `canGoForward: bool`
* `progress: float`


#### `webViewNavigation`

Has the below keys, which can be accessed with `##`.

* `target: ReactNative.NativeTypes.nodeHandle`
* `url: string`
* `title: string`
* `loading: bool`
* `canGoBack: bool`
* `canGoForward: bool`
* `navigationType: ReactNativeWebView_NavigationType.t`
* `mainDocumentURL: option(string)`


#### `webViewShouldStartLoadWithRequest`

Has the below keys, which can be accessed with `##`.

* `target: ReactNative.NativeTypes.nodeHandle`
* `url: string`
* `title: string`
* `loading: bool`
* `canGoBack: bool`
* `canGoForward: bool`
* `navigationType: ReactNativeWebView_NavigationType.t`
* `mainDocumentURL: option(string)`
* `lockIdentifier: int`


#### `webViewErrorEvent`
```reason
type webViewErrorEvent =
  ReactNative.Event.syntheticEvent(Js.t(webViewError));
```

passed to the handler specified for [`onError`](#onerror-webviewerrorevent--unit)

#### `webViewHttpErrorEvent`
```reason
type webViewHttpErrorEvent =
  ReactNative.Event.syntheticEvent(Js.t(webViewHttpError));
```

passed to the handler specified for [`onHttpError`](#onhttperror-webviewhttperrorevent--unit)

#### `webViewMessageEvent`
```reason
type webViewMessageEvent =
  ReactNative.Event.syntheticEvent(Js.t(webViewMessage));
```

passed to the handler specified for [`onMessage`](#onmessage-webviewmessageevent--unit)

#### `webViewNavigationEvent`
```reason
type webViewNavigationEvent =
  ReactNative.Event.syntheticEvent(Js.t(webViewNavigation));
```

passed to handlers specified for [`onLoad`](#onload-webviewnavigationevent--unit) or [`onLoadStart`](#onloadstart-webviewnavigationevent--unit)

#### `webViewProgressEvent`
```reason
type webViewProgressEvent =
  ReactNative.Event.syntheticEvent(Js.t(webViewNativeProgressEvent));
```

passed to the handler specified for [`onLoadProgress`](#onloadprogress-webviewprogressevent--unit)

#### `webViewTerminatedEvent`
```reason
type webViewTerminatedEvent =
  ReactNative.Event.syntheticEvent(webViewNativeEvent);
```

passed to the handler specified for [`onContentProcessDidTerminate`](#oncontentprocessdidterminate-webviewterminatedevent--unit)


#### `webViewNavigationOrError`

Union type passed to the handler specified for [`onLoadEnd`](#onloadend-unioncallbackt), is of type [`webViewNavigationEvent`](#webviewnavigationevent) if loading succeeds and [`webViewErrorEvent`](#webviewerrorevent) if it fails.

Refer to [`UnionCallback.t`](#unioncallbackt) for information on how to create the appropriate handler.

### Props

### `ref: ref` 

Should be specified to be able to access the `WebView` instance and apply [`methods`](#methods). Also refer to [`element`](#element) and [`ref`](#ref).

As an alternative, refer to [React documentation on `forwardRef`](https://reactjs.org/docs/forwarding-refs.html).

#### `allowingReadAccessToURL: string`

Specifies URLs which can be referenced in scripts, AJAX requests and CSS imports. Used only for URIs specified as `file://`. Defaults to the URL provided in the URI.

#### `allowFileAccess: bool`

Allows access to the file system via URI specified as `file://` when `true`, defaults to false.

#### `allowUniversalAccessFromFileURLs: bool`

JavaScript running in the context of a file scheme URL should be allowed access to content from any origin including content from other file scheme URLs when `true`, defaults to `false`.

#### `allowsBackForwardNavigationGestures: bool`

_iOS only_

Horizontal swipe gestures are allowed when `true`, defaults to `false`.

#### `allowsFullscreenVideo: bool`

Fullscreen playback of videos is allowed when `true`, defaults to `false`.

#### `allowsInlineMediaPlayback: bool`

Determines whether HTML5 videos play inline or use the native full-screen controller, defaults `false`.

#### `allowsLinkPreview: bool`

_iOS only_ _required 3D Touch support_

Pressing on a link displays a preview of the target when `true`. Defaults to `true` on iOS 10 and later, to `false` otherwise.

#### `androidHardwareAccelerationDisabled: bool`

_Android only_

Disables Hardware Acceleration in the WebView when `true`, defaults to `false`.

#### `applicationNameForUserAgent: string`

Specifies `string` value to append to the `User-Agent` header, will be overridden if `userAgent` is set.

For example when `applicationNameForUserAgent="DemoApp/1.1.0"` as below:

```reason
<ReactNativeWebView
  source=ReactNativeWebView.Source.uri(~uri="https://facebook.github.io/react-native", ())
  applicationNameForUserAgent="DemoApp/1.1.0"
/>
```

Resulting `User-Agent` may be as below:

##### Android
```
Mozilla/5.0 (Linux; Android 8.1.0; Android SDK built for x86 Build/OSM1.180201.021; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/61.0.3163.98 Mobile Safari/537.36 DemoApp/1.1.0
```

##### iOS
```
Mozilla/5.0 (iPhone; CPU iPhone OS 12_2 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Mobile/15E148 DemoApp/1.1.0
```

#### `automaticallyAdjustContentInsets: bool`

Controls whether to adjust the content inset for web views that are placed behind a navigation bar, tab bar, or toolbar. The default value is true.

#### `bounces: bool`

WebView bounces as edge of the content is reached when `true`, defaults to `true`.

#### `cacheEnabled: bool`

Sets whether WebView should use browser caching, defaults to `true`.

#### ``cacheEnabled: [ | `default | `cacheOnly | `cacheElseNetwork  | `noCache ]``

Overrides default caching behavior, which depends on the navigation type. For a normal page load, cache is checked and content is revalidated as needed. When navigating back, content is not revalidated, but simply retrieved from the cache.

| Value  | Behavior  |
|:--|:--|
| `` `default`` | Default cache usage mode. If the navigation type doesn't impose any specific behavior, use cached resources when they are available and not expired, otherwise load resources from the network. |
| `` `cacheOnly`` | Don't use the network, load resources from the cache. |
| `` `cacheElseNetwork`` | Use cached resources when available, even when expired. Otherwise, load resources from the network. |
| `` `noCache`` | Don't use the cache, load resources from the network. |

#### `containerStyle: ReactNative.Style.t`

allows to customize the WebView container style. Please note that there are default styles (example: `~flex=0.` needs to be specified to use the `height` prop).

#### `contentInset: ReactNative.View.edgeInsets`

Refer to [`reason-react-native` documentation on View](https://github.com/reason-react-native/reason-react-native/blob/master/src/components/View.md). 

#### ``contentInsetAdjustmentBehavior: [ | `never | `always | `automatic | `scrollableAxes]``

_iOS only_

Specifies how safe area insets are used to modify content area of the scroll view, defaults to `` `never``. Available on iOS 11 and later.

#### `dataDetectorTypes: array(DataDetectorTypes.t)`

Specifies types of data to be converted to clickable URLs in content of the WebView, defaults to `[|DataDetectorTypes.phoneNumber|]`. Refer to [`DataDetectorTypes.t`](#datadetectortypest) for all valid values.

#### `decelerationRate: DecelerationRate.t`

_iOS only_

Specifies how quickly the scroll view should decelerate once the user lifts their finger. Refer to [`DecelerationRate.t`](#decelerationratet) for all valid values.

#### `directionalLockEnabled: bool`

_iOS only_

Disables scrolling in a particular direction when `true`, defaults to `true`.

#### `domStorageEnabled: bool`

_Android only_

DOM Storage is enabled when `true`.

#### `geolocationEnabled: bool`

_Android only_

Set whether geolocation is enabled in the `WebView`, defaults to `false.`

#### `hideKeyboardAccessoryView: bool`

_iOS only_

Keyboard accessory view will be hidden when `true`.

#### `incognito: bool`

Does not store any data within the lifetime of the `WebView.`

#### `injectedJavaScript: string`

Specifies JavaScript that will be injected into the web page when loaded. The string should evaluate to a valid type (e.g. `true`) and not otherwise throw an exception.

```reason
let injectedJavaScript = "(function() {
  window.ReactNativeWebView.postMessage(JSON.stringify(window.location));
})();";

<ReactNativeWebView
  source=ReactNativeWebView.Source.uri(~uri="https://facebook.github.io/react-native", ())
  injectedJavaScript=injectedJavaScript
  onMessage={e => Js.Console.warn(e##nativeEvent##data)}
/>
```

Note that the JavaScript will only be run once when the page is loaded for the first time; it will not be run again even if the page is reloaded or navigated away.

Refer to the [Communicating between JS and Native](https://github.com/react-native-community/react-native-webview/blob/master/docs/Guide.md#communicating-between-js-and-native) guide for more information.

#### `javaScriptEnabled: bool`

_Android only_

Enables JavaScript in the WebView when `true`, defaults to `true`. JavaScript is already enabled by default on iOS.

#### `keyboardDisplayRequiresUserAction: bool`

_iOS only_

Web content can programmatically display the keyboard when `false`, defaults to `true`.

#### `mediaPlaybackRequiresUserAction: bool`

HTML5 audio and video playback requires the user to tap them when `true`, defaults to `true`.

Some videos may hang while loading on iOS when `true`. As the props defaults to `true`, setting `mediaPlaybackRequiresUserAction=false` may fix this issue.

#### ``mixedContentMode: [@bs.string] [ | `never | `always | `compatibility]``

_Android only_

Specifies mixed content mode, defaults to `` `never``.

| Value  | Behavior  |
|:--|:--|
| `` `never`` | WebView will not allow a secure origin to load content from an insecure origin. |
| `` `always`` | WebView will allow a secure origin to load content from any other (even insecure) origin. |
| `` `compatibility`` | WebView will attempt to be compatible with how modern web browsers treat mixed content. |

#### `nativeConfig: nativeConfig`

Overrides the native component used to render the `WebView`. Enables a custom native `WebView` which uses the same JavaScript as the original WebView. Refer to the [`nativeConfig`](#nativeconfig) type on how to specify the custom component.

You may refer to [iOS-](https://github.com/react-native-community/react-native-webview/blob/master/docs/Custom-iOS.md) and [Android-](https://github.com/react-native-community/react-native-webview/blob/master/docs/Custom-Android.md)specific guides on how to create a custom `WebView`.

#### `onContentProcessDidTerminate: webViewTerminatedEvent => unit`

_iOS only_

Specifies function to be invoked when the WebView content process is terminated. The process may be terminated due to reasons such as running too long or using too many resources, however, once terminated a blank page is displayed and the `WebView` becomes unusable. Please refer to the [PR](https://github.com/react-native-community/react-native-webview/pull/774) which added the functionality to allow handling this issue.

```reason
<ReactNativeWebView
  source=ReactNativeWebView.Source.uri(~uri="https://facebook.github.io/react-native", ())
  onContentProcessDidTerminate={_ => 
    ReactNativeWebView.reload()

    this.refs.webview.reload();
  }}
/>
```

#### `onError: webViewErrorEvent => unit`

Specifies function to be invoked when the `WebView` fails to load.

#### `onLoad: webViewNavigationEvent => unit`

Specifies function to be invoked when the `WebView` has finished loading.

#### `onLoadEnd: UnionCallback.t`

Specifies function to be invoked when the `WebView` succeeds or fails to load.

#### `onLoadProgress: webViewProgressEvent => unit`

Specifies function to be invoked while the `WebView` is loading.

#### `onLoadStart: webViewNavigationEvent => unit`

Specifies function to be invoked when the `WebView` starts to load.

#### `onMessage: webViewMessageEvent => unit`

Specifies function to be invoked when the `WebView` calls `window.ReactNativeWebView.postMessage`. Setting this prop will inject that global into the webview.

`window.ReactNativeWebView.postMessage` accepts one `string` argument, which will be available as e.g. `e##nativeEvent##data` where `e` is the event object.

Refer to the [Communicating between JS and Native](https://github.com/react-native-community/react-native-webview/blob/master/docs/Guide.md#communicating-between-js-and-native) guide for more information.

#### `onNavigationStateChange: Js.t(webViewNavigation) => unit`

Specifies function to be invoked when the WebView starts or ends loading.

Note that this method will not be invoked on hash URL changes (e.g. from https://example.com/users#list to https://example.com/users#help). A workaround may be found in the [Guide](https://github.com/react-native-community/react-native-webview/blob/master/docs/Guide.md#intercepting-hash-url-changes).

#### `onShouldStartLoadWithRequest: Js.t(webViewShouldStartLoadWithRequest) => bool`

Allows custom handling of any `WebView` requests. Specified function should return `true` to allow requests and `false` to stop loading.

On Android, the function is not called on first load.

#### `originWhitelist: array(string)`

Specifies `array(string)` listing origin strings to which navigation is allowed. Strings will be matched against just the origin (not the full URL) and wildcards are allowed. Any URL not whitelisted will be handled by the OS. Defaults to `[|"http://", "https://"|]`.

#### ``overScrollMode: [ | `never | `always | `content]``

_Android only_

Specifies the over scroll mode, defaults to `` `always``.

| Value  | Behavior  |
|:--|:--|
| `` `always`` | Always allow a user to over-scroll the view if scrollable |
| `` `never`` | Never allow a user to over-scroll the view |
| `` `content`` | Allow a user to over-scroll the view only if scrollable and the content is large enough |


#### `pagingEnabled: bool`

_iOS only_

As the user scrolls, scroll view stops on multiples of the its bounds when `true`, defaults to `false`.

#### `renderError: string => React.element`

Specifies a function to be invoked when there is an error.

```reason
<ReactNativeWebView
  source=ReactNativeWebView.Source.uri(~uri="https://facebook.github.io/react-native", ())
  renderError={errorName => <Error name=errorName />}
/>
```

#### `renderLoading: unit => React.element`

Specifies a function to be invoked when the `WebView` is loading.  Requires setting `startInLoadingState=true` .

```reason
<ReactNativeWebView
  source=ReactNativeWebView.Source.uri(~uri="https://facebook.github.io/react-native", ())
  startInLoadingState=true
  renderLoading={() => <Loading />}
/>
```

#### `saveFormDataDisabled: bool`

_Android only_

`bool` determines whether the WebView should disable saving form data., defaults to `false`. Has no effect on Android API level 26 and abovem as there is an Autofill feature storing form data.

#### `scalesPageToFit: bool`

_Android only_

Web content is scaled to fit the view and the user may change the scale when `true`, defaults to `true`.

#### `scrollEnabled: bool`

_iOS only_

Enables scrolling in the WebView, defaults to `true`. When `false`, document body will not be moved if the keyboard obstructs an input.

#### `sharedCookiesEnabled: bool`

_iOS only_

When set `true`, shared cookies from `[NSHTTPCookieStorage sharedHTTPCookieStorage]` should be used for every load request in the WebView, defaults to `false`.

#### `showsHorizontalScrollIndicator: bool`

Horizontal scroll indicator is shown in the WebView when `true`, defaults to `true`.

#### `showsVerticalScrollIndicator: bool`

Vertical scroll indicator is shown in the WebView when `true`, defaults to `true`.

#### `source: Source.t`

Specifies the resource to be loaded in the WebView as static HTML or a URI (with optional headers). Note that setting originWhitelist to `[|"*"|]` is required when source is some static HTML. Refer to [Source.t](#sourcet) for information on how to create the appropriate type.

#### `startInLoadingState: bool`

Forces the WebView to show the loading view on first load; must be set to `true` for the `renderLoading` prop to work.

#### `textZoom: float`

_Android only_

Resolves issue where custom font sizes on Android leads to undesirable scaling of the interface when set to `100.0` (i.e. `textZoom=100.0`).

#### `thirdPartyCookiesEnabled: bool`

Enables third party cookies in WebView when `true`, defaults to `true` on iOS and Android versions below 5.0.

#### `userAgent: string`

Specifies `User-Agent` header for the WebView

### `View` props

Refer to
[`@reason-react-native/react-native`](https://github.com/reason-react-native/react-native)
[documentation](https://reasonml-community.github.io/reason-react-native/en/docs/components/View/).

Please do note the below:

#### `style: ReactNative.Style.t`

allows to customize the WebView style. Please note that there are default styles (example: `~flex=0.` needs to be specified to use the `height` prop).

### Methods

For the methods below, `element` representing the `WebView` instance needs to be determined from the `ref` which itself can be defined and passed to the `WebView` as below:

```reason
let ref = React.createRef();

<ReactNativeWebView
  ref=ref
```

The `element` can be determined and the method [`reload`](#reload-element--unit) may be called as below:
```reason
switch (ref -> React.Ref.current -> Js.Nullable.toOption) {
| None => Js.Console.warn("no element")
| Some(e) => ReactNativeWebView.reload(e)
};
```

#### `goBack: element => unit`

Navigates back one page in the WebView history.

#### `goForward: element => unit`

Navigates forward one page in the WebView history.

#### `reload: element => unit`

Reloads the current page.

#### `stopLoading: element => unit`

Stop loading the current page.

#### `injectJavaScript: (T.t, string) => unit`

Injects JavaScript as `string` into the web page. The string should evaluate to a valid type (e.g. `true`) and not otherwise throw an exception.

Refer to the [Communicating between JS and Native](https://github.com/react-native-community/react-native-webview/blob/master/docs/Guide.md#communicating-between-js-and-native) guide for more information.

---

## Changelog

Check the [changelog](./CHANGELOG.md) for more information about recent
releases.

## Contribute

Read the [contribution guidelines](./CONTRIBUTING.md) before contributing.

## Code of Conduct

We want this community to be friendly and respectful to each other. Please read
[our full code of conduct](./CODE_OF_CONDUCT.md) so that you can understand what
actions will and will not be tolerated.

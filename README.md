---

# `@reason-react-native/webview`

[![Build Status](https://github.com/reason-react-native/webview/workflows/Build/badge.svg)](https://github.com/reason-react-native/webview/actions)
[![Version](https://img.shields.io/npm/v/@reason-react-native/webview.svg)](https://www.npmjs.com/@reason-react-native/webview)
[![Chat](https://img.shields.io/discord/235176658175262720.svg?logo=discord&colorb=blue)](https://reasonml-community.github.io/reason-react-native/discord/)

[ReasonML](https://reasonml.github.io) /
[BuckleScript](https://bucklescript.github.io) bindings for
[`react-native-webview`](https://github.com/react-native-community/react-native-webview).

Exposed as the `ReactNativeWebView` module.

Version x.y.z of `@reason-react-native/webview` is intended to be compatible with version x.y.z of `@react-native-community/react-native-webview`.

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
    "@reason-react-native/react-native",
    // ...
+    "@reason-react-native/webview"
  ],
  //...
}
```

## Usage

Documentation will be added later.

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

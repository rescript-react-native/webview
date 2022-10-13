'use strict';

var Curry = require("rescript/lib/js/curry.js");
var Event$ReactNative = require("rescript-react-native/src/apis/Event.bs.js");
var NativeElement$ReactNative = require("rescript-react-native/src/elements/NativeElement.bs.js");

function Make(funarg) {
  Event$ReactNative.SyntheticEvent({});
  var make = function (navigationCallback, errorCallback, x) {
    var match = x.nativeEvent.description;
    if (match !== undefined) {
      return Curry._1(errorCallback, x);
    } else {
      return Curry._1(navigationCallback, x);
    }
  };
  var uncurriedMake = function (navigationCallback, errorCallback, x) {
    var match = x.nativeEvent.description;
    if (match !== undefined) {
      return errorCallback(x);
    } else {
      return navigationCallback(x);
    }
  };
  return {
          make: make,
          uncurriedMake: uncurriedMake
        };
}

exports.Make = Make;
/* NativeElement-ReactNative Not a pure module */

'use strict';

var Curry = require("bs-platform/lib/js/curry.js");

function Make(T) {
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
/* No side effect */

// Generated by ReScript, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Future = require("reason-future/src/Future.bs.js");
var Caml_js_exceptions = require("bs-platform/lib/js/caml_js_exceptions.js");

var allEntities = {
  hd: "Apple",
  tl: {
    hd: "Banana",
    tl: {
      hd: "All",
      tl: {
        hd: "Berry",
        tl: /* [] */0
      }
    }
  }
};

function contain(target, search) {
  return new RegExp(search).test(target);
}

console.log(List.filter(function (__x) {
            return new RegExp("a").test(__x);
          })(allEntities));

List.filter(function (__x) {
        return new RegExp("text").test(__x);
      })(allEntities);

function xtest(text) {
  return List.filter(function (__x) {
                return new RegExp(text).test(__x);
              })(allEntities);
}

function parseJsonResult(text) {
  var result = {
    TAG: 0,
    _0: List.filter(function (__x) {
            return new RegExp(text).test(__x);
          })(allEntities),
    [Symbol.for("name")]: "Ok"
  };
  var value;
  try {
    value = result;
  }
  catch (raw_exn){
    var exn = Caml_js_exceptions.internalToOCamlException(raw_exn);
    return {
            TAG: 1,
            _0: exn,
            [Symbol.for("name")]: "Error"
          };
  }
  return {
          TAG: 0,
          _0: value._0,
          [Symbol.for("name")]: "Ok"
        };
}

function findEntities(text) {
  return Future.make(undefined, (function (resolve) {
                return Curry._1(resolve, {
                            TAG: 0,
                            _0: List.filter(function (__x) {
                                    return new RegExp(text).test(__x);
                                  })(allEntities),
                            [Symbol.for("name")]: "Ok"
                          });
              }));
}

function make(text, param) {
  return Future.make(undefined, (function (resolve) {
                return Curry._1(resolve, {
                            TAG: 0,
                            _0: parseJsonResult(text),
                            [Symbol.for("name")]: "Ok"
                          });
              }));
}

var x = Future.map(make("a", undefined), (function (x) {
        console.log("incr(future2Counter)", x);
        
      }));

Future.get(Future.value(undefined, make("a", undefined)), (function (value) {
        console.log("incr(future2Counter)", value);
        
      }));

var allEntities$1 = {
  hd: "Apple",
  tl: {
    hd: "Banana",
    tl: {
      hd: "All",
      tl: {
        hd: "Berry",
        tl: /* [] */0
      }
    }
  }
};

exports.contain = contain;
exports.xtest = xtest;
exports.parseJsonResult = parseJsonResult;
exports.findEntities = findEntities;
exports.allEntities = allEntities$1;
exports.make = make;
exports.x = x;
/*  Not a pure module */

// Generated by BUCKLESCRIPT VERSION 4.0.6, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Welcome = require("./views/Welcome.bs.js");
var FetchScreen = require("./views/FetchScreen.bs.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var PlaylistCreator = require("./views/PlaylistCreator.bs.js");

function reducer(action, _) {
  return /* Update */Block.__(0, [/* record */[/* route */action[0]]]);
}

function mapUrlToRoute(url) {
  var match = url[/* path */0];
  if (match) {
    switch (match[0]) {
      case "create-playlists" : 
          if (match[1]) {
            return /* Welcome */0;
          } else {
            return /* PlaylistCreator */2;
          }
      case "fetching" : 
          if (match[1]) {
            return /* Welcome */0;
          } else {
            return /* FetchScreen */1;
          }
      default:
        return /* Welcome */0;
    }
  } else {
    return /* Welcome */0;
  }
}

var component = ReasonReact.reducerComponent("App");

function make() {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              Curry._1(self[/* send */3], /* ChangeRoute */[mapUrlToRoute(ReasonReact.Router[/* dangerouslyGetInitialUrl */3](/* () */0))]);
              var watchId = ReasonReact.Router[/* watchUrl */1]((function (url) {
                      return Curry._1(self[/* send */3], /* ChangeRoute */[mapUrlToRoute(url)]);
                    }));
              return Curry._1(self[/* onUnmount */4], (function () {
                            return ReasonReact.Router[/* unwatchUrl */2](watchId);
                          }));
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var match = self[/* state */1][/* route */0];
              switch (match) {
                case 0 : 
                    return ReasonReact.element(undefined, undefined, Welcome.make(/* array */[]));
                case 1 : 
                    return ReasonReact.element(undefined, undefined, FetchScreen.make(/* array */[]));
                case 2 : 
                    return ReasonReact.element(undefined, undefined, PlaylistCreator.make(/* array */[]));
                
              }
            }),
          /* initialState */(function () {
              return /* record */[/* route : Welcome */0];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */reducer,
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

var $$default = ReasonReact.wrapReasonForJs(component, (function () {
        return make(/* array */[]);
      }));

exports.reducer = reducer;
exports.mapUrlToRoute = mapUrlToRoute;
exports.component = component;
exports.make = make;
exports.$$default = $$default;
exports.default = $$default;
exports.__esModule = true;
/* component Not a pure module */

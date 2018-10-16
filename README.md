# bs-react-navigation

[Reason](https://reasonml.github.io) bindings to [react-navigation](https://github.com/react-navigation/react-navigation).

## Status

WIP WIP WIP WIP

## Examples

A screen component with dynamic navigation options (Screen1.re):

```reason
open BsReactNative;
open ReactNavigation;

let component = ReasonReact.statelessComponent(__MODULE__);

let make = (~navigation, ~screenProps, _children) => {
  ...component,
  render: _self => <Text> {ReasonReact.string("Hello world!")} </Text>,
};

let reactClass =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(~navigation=jsProps##navigation, ~screenProps=jsProps##screenProps, [||])
  );

reactClass->setDynamicNavigationOptions(params => {
  let navigation = params->NavigationParams.navigationGet;
  let navigationOptions = params->NavigationParams.navigationOptionsGet;
  let screenProps = params->NavigationParams.screenPropsGet;

  /* More properties can be set dynamically based on navigation, navigationOptions or screenProps. */
  NavigationOptions.t(~title="Screen 1", ~headerTintColor="red", ());
});
```

Using it:

```reason
open ReactNavigation;

let routes = {
  "Screen1": Screen1.reactClass,
  "Screen2": Screen2.reactClass,
  "Screen3": Screen3.reactClass,
};

let reactClass = StackNavigator.make(routes);

reactClass->setNavigationOptions(NavigationOptions.t(~gesturesEnabled=false, ()));
```

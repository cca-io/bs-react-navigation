# bs-react-navigation

[Reason](https://reasonml.github.io) bindings to [react-navigation](https://github.com/react-navigation/react-navigation).

## Status

WIP WIP WIP WIP

## Examples

A screen component with dynamic navigation options (Screen1.re):

```reason
open ReactNative;
open ReactNavigation;

[@react.component]
let make = (~navigation, ~screenProps) => {
  <Text> {React.string("Hello world!")} </Text>,
};

make->setDynamicNavigationOptions(params => {
  let navigation = params->NavigationParams.navigation;
  let navigationOptions = params->NavigationParams.navigationOptions;
  let screenProps = params->NavigationParams.screenProps;

  /* More properties can be set dynamically based on navigation, navigationOptions or screenProps. */
  NavigationOptions.t(~title="Screen 1", ~headerTintColor="red", ());
});
```

Using it:

```reason
open ReactNavigation;

let routes = {
  "Screen1": Screen1.make,
  "Screen2": Screen2.make,
  "Screen3": Screen3.make,
};

let navigator = StackNavigator.make(routes);

navigator->setNavigationOptions(NavigationOptions.t(~gesturesEnabled=false, ()));
```

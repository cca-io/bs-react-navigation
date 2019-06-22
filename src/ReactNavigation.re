open ReactNative;

module NavigationState = {
  [@bs.deriving {abstract: light}]
  type t = {
    index: int,
    [@bs.optional]
    routes: array(t),
    isDrawerOpen: bool,
  };
};

module NavigationActions = {
  type action;

  [@bs.deriving {abstract: light}]
  type navigateParams = {
    routeName: string,
    [@bs.optional]
    params: Js.t({.}),
  };

  [@bs.deriving {abstract: light}]
  type backParams = {
    [@bs.optional]
    key: string,
    [@bs.optional]
    immediate: bool,
  };

  [@bs.module "react-navigation"] [@bs.scope "NavigationActions"]
  external navigate: navigateParams => action = "";

  [@bs.module "react-navigation"] [@bs.scope "NavigationActions"]
  external back: backParams => action = "";
};

module NavigationContainer = {
  type t;

  [@bs.send] external dispatch: (t, NavigationActions.action) => unit = "";
};

module Navigation = {
  [@bs.deriving {abstract: light}]
  type t = {state: NavigationState.t};

  [@bs.send] external navigate: (t, string) => unit = "";
  [@bs.send]
  external navigateWithParams: (t, string, Js.t({..})) => unit = "navigate";
  [@bs.send] external pop: (t, unit) => unit = "";
  [@bs.send] external openDrawer: (t, unit) => unit = "";
  [@bs.send] external getParam: (t, string, 'a) => 'a = "";
};

type navigatorProps;
type navigator = React.component(navigatorProps);

module StackNavigator = {
  module Config = {
    [@bs.deriving {abstract: light}]
    type t = {
      [@bs.optional]
      mode: string, /* "card" or "modal" */
      [@bs.optional]
      headerMode: string /* float|screen|none */
      /* TODO: further props */
    };
  };

  [@bs.module "react-navigation"]
  external make: Js.t('a) => navigator = "createStackNavigator";

  [@bs.module "react-navigation"]
  external makeWithConfig: (Js.t('a), Config.t) => navigator =
    "createStackNavigator";
};

module DrawerNavigator = {
  module ContentComponent = {
    [@bs.deriving {abstract: light}]
    type props('screenProps) = {
      navigation: Navigation.t,
      screenProps: 'screenProps,
    };

    type t('screenProps) = React.component(props('screenProps));
  };

  [@bs.module "react-navigation"]
  external drawerItems: ContentComponent.t('screenProps) = "DrawerItems";

  module Config = {
    module ContentOptions = {
      [@bs.deriving {abstract: light}]
      type t = {
        [@bs.optional]
        activeTintColor: string,
        [@bs.optional]
        activeBackgroundColor: string,
        [@bs.optional]
        inactiveTintColor: string,
        [@bs.optional]
        inactiveBackgroundColor: string,
        /* onItemPress(route) - function to be invoked when an item is pressed */
        [@bs.optional]
        itemsContainerStyle: Style.t,
        [@bs.optional]
        itemStyle: Style.t,
        [@bs.optional]
        labelStyle: Style.t,
        [@bs.optional]
        activeLabelStyle: Style.t,
        [@bs.optional]
        inactiveLabelStyle: Style.t,
        [@bs.optional]
        iconContainerStyle: Style.t,
      };
    };

    [@bs.deriving {abstract: light}]
    type t('screenProps) = {
      [@bs.optional]
      drawerWidth: float,
      [@bs.optional]
      drawerPosition: string, /* "left" or "right" */
      [@bs.optional]
      contentComponent: ContentComponent.t('screenProps),
      [@bs.optional]
      contentOptions: ContentOptions.t,
      [@bs.optional]
      useNativeAnimations: bool,
      [@bs.optional]
      drawerBackgroundColor: string,
      [@bs.optional]
      initialRouteName: string,
      /* [@bs.optional]
         paths: ??, */
      [@bs.optional]
      backBehavior: string /* "initialRoute" or "none" */
    };
  };

  [@bs.module "react-navigation"]
  external make: Js.t('a) => navigator = "createDrawerNavigator";

  [@bs.module "react-navigation"]
  external makeWithConfig: (Js.t('a), Config.t('screenProps)) => navigator =
    "createDrawerNavigator";
};

module TabNavigator = {
  module TabBarOptions = {
    [@bs.deriving {abstract: light}]
    type t = {
      [@bs.optional]
      activeTintColor: string,
      [@bs.optional]
      inactiveTintColor: string,
      [@bs.optional]
      showIcon: bool,
      [@bs.optional]
      showLabel: bool,
      [@bs.optional]
      upperCaseLabel: bool,
      [@bs.optional]
      pressColor: string,
      [@bs.optional]
      pressOpacity: float,
      [@bs.optional]
      scrollEnabled: bool,
      [@bs.optional]
      tabStyle: Style.t,
      [@bs.optional]
      indicatorStyle: Style.t,
      [@bs.optional]
      labelStyle: Style.t,
      [@bs.optional]
      iconStyle: Style.t,
      [@bs.optional]
      style: Style.t,
      [@bs.optional]
      allowFontScaling: bool,
    };
  };

  module Config = {
    [@bs.deriving {abstract: light}]
    type t = {
      [@bs.optional]
      backBehavior: string,
      [@bs.optional]
      swipeEnabled: bool,
      [@bs.optional]
      animationEnabled: bool,
      [@bs.optional] [@bs.as "lazy"]
      lazy_: bool,
      [@bs.optional]
      tabBarOptions: TabBarOptions.t,
      /* TODO: more props */
    };
  };

  [@bs.module "react-navigation"]
  external makeMaterialTopNavigator: Js.t('a) => navigator =
    "createMaterialTopTabNavigator";

  [@bs.module "react-navigation"]
  external makeMaterialTopNavigatorWithConfig:
    (Js.t('a), Config.t) => navigator =
    "createMaterialTopTabNavigator";
};

module NavigationOptions = {
  [@bs.deriving {abstract: light}]
  type t = {
    [@bs.optional]
    title: string,
    /* header: option [ | `custom (headerProps => React.element) | `notVisible], */
    [@bs.optional]
    headerTitle: React.element,
    [@bs.optional]
    headerTitleStyle: Style.t,
    [@bs.optional]
    headerTintColor: string,
    [@bs.optional]
    headerBackTitle: Js.Nullable.t(string),
    [@bs.optional]
    headerTruncatedBackTitle: string,
    [@bs.optional]
    headerLeft: React.element,
    [@bs.optional]
    headerBackTitleStyle: Style.t,
    [@bs.optional]
    headerPressColorAndroid: string,
    [@bs.optional]
    headerRight: React.element,
    [@bs.optional]
    headerStyle: Style.t,
    [@bs.optional]
    gesturesEnabled: bool,
    /* Drawer Navigator */
    [@bs.optional]
    drawerIcon: React.element,
    [@bs.optional]
    drawerLabel: string,
    /* {
         .
         "focused": bool,
         "tintColor": string,
       } =>
       React.element, */
    [@bs.optional]
    drawerLockMode: string /* unlocked | locked-closed | locked-open */
  };
};
module NavigationParams = {
  [@bs.deriving {abstract: light}]
  type t('screenProps) = {
    navigation: Navigation.t,
    navigationOptions: NavigationOptions.t,
    screenProps: 'screenProps,
  };
};

module AppContainer = {
  type props;

  [@bs.module "react-navigation"]
  external make: navigator => React.component(props) = "createAppContainer";
};

[@bs.set]
external setNavigationOptions:
  (React.component('props), NavigationOptions.t) => unit =
  "navigationOptions";
[@bs.set]
external setDynamicNavigationOptions:
  (React.component('props), NavigationParams.t('a) => NavigationOptions.t) =>
  unit =
  "navigationOptions";
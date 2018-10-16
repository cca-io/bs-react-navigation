open BsReactNative;

module NavigationState = {
  [@bs.deriving abstract]
  type t = {
    index: int,
    [@bs.optional]
    routes: array(t),
    isDrawerOpen: bool,
  };
};

module Navigation = {
  [@bs.deriving abstract]
  type t = {state: NavigationState.t};

  [@bs.send] external navigate: (t, string) => unit = "";
  [@bs.send] external navigateWithParams: (t, string, Js.t({..})) => unit = "navigate";
  [@bs.send] external pop: (t, unit) => unit = "";
  [@bs.send] external openDrawer: (t, unit) => unit = "";
  [@bs.send] external getParam: (t, string, 'a) => 'a = "";
};

module StackNavigator = {
  module Config = {
    [@bs.deriving abstract]
    type t = {
      [@bs.optional]
      mode: string, /* "card" or "modal" */
      [@bs.optional]
      headerMode: string /* float|screen|none */
      /* TODO: further props */
    };
  };

  [@bs.module "react-navigation"] external make: Js.t('a) => ReasonReact.reactClass = "createStackNavigator";

  [@bs.module "react-navigation"]
  external makeWithConfig: (Js.t('a), Config.t) => ReasonReact.reactClass = "createStackNavigator";
};

module DrawerNavigator = {
  [@bs.module "react-navigation"] external drawerItemsClass: ReasonReact.reactClass = "DrawerItems";

  module Config = {
    module ContentOptions = {
      [@bs.deriving abstract]
      type t = {
        [@bs.optional]
        activeTintColor: string,
        [@bs.optional]
        activeBackgroundColor: string,
        [@bs.optional]
        style: Style.t,
      };
    };

    [@bs.deriving abstract]
    type t = {
      [@bs.optional]
      drawerWidth: float,
      [@bs.optional]
      drawerPosition: string, /* "left" or "right" */
      [@bs.optional]
      contentComponent: ReasonReact.reactClass,
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

  [@bs.module "react-navigation"] external make: Js.t('a) => ReasonReact.reactClass = "createDrawerNavigator";

  [@bs.module "react-navigation"]
  external makeWithConfig: (Js.t('a), Config.t) => ReasonReact.reactClass = "createDrawerNavigator";
};

module TabNavigator = {
  module TabBarOptions = {
    [@bs.deriving abstract]
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
    [@bs.deriving abstract]
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
  external makeMaterialTopNavigator: Js.t('a) => ReasonReact.reactClass = "createMaterialTopTabNavigator";

  [@bs.module "react-navigation"]
  external makeMaterialTopNavigatorWithConfig: (Js.t('a), Config.t) => ReasonReact.reactClass =
    "createMaterialTopTabNavigator";
};

module NavigationOptions = {
  [@bs.deriving abstract]
  type t = {
    [@bs.optional]
    title: string,
    /* header: option [ | `custom (headerProps => ReasonReact.reactElement) | `notVisible], */
    [@bs.optional]
    headerTitle: ReasonReact.reactElement,
    [@bs.optional]
    headerTitleStyle: Style.t,
    [@bs.optional]
    headerTintColor: string,
    [@bs.optional]
    headerBackTitle: Js.Nullable.t(string),
    [@bs.optional]
    headerTruncatedBackTitle: string,
    [@bs.optional]
    headerLeft: ReasonReact.reactElement,
    [@bs.optional]
    headerBackTitleStyle: Style.t,
    [@bs.optional]
    headerPressColorAndroid: string,
    [@bs.optional]
    headerRight: ReasonReact.reactElement,
    [@bs.optional]
    headerStyle: Style.t,
    [@bs.optional]
    gesturesEnabled: bool,
    /* Drawer Navigator */
    [@bs.optional]
    drawerIcon: ReasonReact.reactElement,
    [@bs.optional]
    drawerLabel: ReasonReact.reactElement,
    [@bs.optional]
    drawerLockMode: string /* unlocked | locked-closed | locked-open */
  };
};

module NavigationParams = {
  [@bs.deriving abstract]
  type t('a) = {
    navigation: Navigation.t,
    navigationOptions: NavigationOptions.t,
    screenProps: 'a,
  };
};

[@bs.set] external setNavigationOptions: (ReasonReact.reactClass, NavigationOptions.t) => unit = "navigationOptions";
[@bs.set]
external setDynamicNavigationOptions: (ReasonReact.reactClass, NavigationParams.t('a) => NavigationOptions.t) => unit =
  "navigationOptions";

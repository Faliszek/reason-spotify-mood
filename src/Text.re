let component = ReasonReact.statelessComponent("Icon");

let make = children => {...component, render: _self => <p> ...children </p>};
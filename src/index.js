import React from "react";
import ReactDOM from "react-dom";

import "./index.css";
import App from "./App.bs";

console.log(localStorage.getItem("reason-spotify-mood"));
ReactDOM.render(<App />, document.getElementById("root"));

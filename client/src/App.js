import logo from './logo.svg';
import React,{Component}from 'react';
import './App.css';

// function App() {
//   return (
//     <div className="App">
//       <header className="App-header">
//         <img src={logo} className="App-logo" alt="logo" />
//         <p>
//           Edit <code>src/App.js</code> and save to reload.
//         </p>
//         <a
//           className="App-link"
//           href="https://reactjs.org"
//           target="_blank"
//           rel="noopener noreferrer"
//         >
//           Learn React
//         </a>
//       </header>
//     </div>
//   );
// }

class App extends Component {

  constructor(props) {
    super(props);
    this.state = {
      isToggleOn: false
    }

    this.handleClick = this.handleClick.bind(this);
  }

  handleClick() {
    //chnage state
    this.setState(state => ({
      isToggleOn : !state.isToggleOn
    }));
  }

  render(){
    return (
      <div id="mainwindow" className="App">
        <h1>FINAL Network Project</h1>
        <p>LED #1</p>
        <button onClick={this.handleClick}>{this.state.isToggleOn ? "ON" : "OFF"}</button>
        <p>LED #2</p>
        <button onClick={this.handleClick}>{this.state.isToggleOn ? "ON" : "OFF"}</button>
      </div>
    );
  }
}

export default App;



let anypiajs = {}

function SetupInterface() {
    // anypiajs.GetAge = ;
    anypiajs.GetAge = function() { console.log("self.Module.cwrap('GetAge', 'string', [])") }
    // anypiajs.GetCalc = function() {  }
    anypiajs.GetCalc = function() { console.log("self.Module.cwrap('GetCalc', 'string', [])") }
}

SetupInterface();

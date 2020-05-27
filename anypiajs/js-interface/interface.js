

let anypiajs = {}



function SetupInterface() {
    // anypiajs.GetAge = self.Module.cwrap('GetAge', 'string', []);
    anypiajs.GetAge = function() { console.log("Getting age") }
}

SetupInterface();

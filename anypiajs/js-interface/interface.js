let anypiajs = {}

function SetupInterface() {

    Module.ccall('InitalizeApplication', 'null', [], []);
    
    anypiajs.GetAge = function() { Module.cwrap('GetAge', 'string', []) }
    anypiajs.GetCalc = function() {  Module.cwrap('GetCalc', 'string', []) }
    anypiajs.GetYears = function() { Module.cwrap('GetYears', 'number', [])}
}

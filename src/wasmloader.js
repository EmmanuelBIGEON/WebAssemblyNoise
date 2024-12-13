var WANModule = {};
const ModuleInit = createWebAssemblyNoiseModule(WANModule);
ModuleInit.then(function(Module) {
    const event = new CustomEvent('ModuleLoaded');
    document.getElementById('canvas').dispatchEvent(event);
  });
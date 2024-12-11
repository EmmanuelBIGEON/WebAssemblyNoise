var WANModule = {};

const ModuleInit = createWebAssemblyNoiseModule(WANModule);
ModuleInit.then(function(Module) {
  var aCanvas = document.getElementById('canvas');
  var aGlCtx = aCanvas.getContext ('webgl2',  { alpha: false, depth: true, antialias: true, preserveDrawingBuffer: false, stencil: true } );
  Module.canvas = aCanvas;
});
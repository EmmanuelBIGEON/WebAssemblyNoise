<template>
  <canvas id="canvas" oncontextmenu="event.preventDefault()" contenteditable="false" width="400" height="400">
  </canvas> 
</template>

<script>

export default {
  name: "MainCanvas",

  mounted () {
    // Import the WebAssembly app
    const canvas = document.getElementById('canvas')
    const gl = canvas.getContext('webgl2',
      { alpha: false, // performance improvement ? dunno.
        depth: false,
        antialias: true, // doesn't work.. do i need a framebuffer ?
        preserveDrawingBuffer: true,
        powerPreference: "high-performance",
        stencil: false 
      });
    const script = document.createElement('script');
    script.src = 'WebAssemblyNoise.js';
    
    // Add listener ModuleLoaded
    document.getElementById('canvas').addEventListener("ModuleLoaded", (event) => {
      this.$emit('moduleLoaded');
    });
    document.head.appendChild(script);
  }
}
</script>

<style scoped>
#canvas
{
  display:block;
  padding: 30px;
  margin:left;
  margin:right;
}
</style>
<template>
  <div id="ShaderView" class="flexcolumn_div">
    <h1 class="not_selectabletext"> WebAssembly Noise </h1>

    
    <div id="ShaderView_content">
      <div class="flexinitial" style="justify-items: center;">
        <select class="selector">
          <option v-for="shader in shaders" :value="shader.id"> {{ shader.name }}</option>
        </select>
        <MainCanvas @moduleLoaded="OnModuleLoad"/>
      </div>  
      <div class="flexauto" style="justify-items: center; max-width: -webkit-fill-available;">
        <Editor :code="currentShaderCode"/>
      </div>  
    </div>
  </div>
</template>
<script>

import MainCanvas from '@/components/MainCanvas.vue';
import Editor from '@/components/Editor.vue';

export default {
  name: 'Shader',
  data () {
    return {
      shaders: [],
      currentShaderCode: "hello"
    }
  },
  components: { MainCanvas, Editor },
  methods: {
    OnModuleLoad () {
      this.shaders = JSON.parse(WANModule.GetShadersJSON())
      if(this.shaders.length)
      {
        WANModule.DisplayShader(this.shaders[0].id)
        this.currentShaderCode = WANModule.GetCurrentShaderCode();
      }
    }
  }
}
</script>

<style scoped>
#ShaderView
{
  align-items: center;
}

#ShaderView_content
{
  display: flex;
  flex-direction: row;
  flex-wrap: wrap;
  width: 100%;
}
</style>

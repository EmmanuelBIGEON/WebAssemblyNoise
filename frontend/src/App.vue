<template>
  <RouterView />
</template>

<script>
import { RouterView } from 'vue-router'

export default {
  name: 'App',
  components: { RouterView }
}
</script>

<style>
#app
{
  min-height: 100%;
  display: flex;
  flex-direction: column;
}

html 
{
  height: 100%;
}

body 
{
  height: 100%;
}

.relative_div
{
  position: relative;
}


.flexrow_div
{
  display: flex;
  flex-direction: row;
}

.flexcolumn_div
{
  display: flex;
  flex-direction: column;
}

.flexauto
{
  flex: auto;
}

.flexinitial
{
  flex: initial;
}

.not_selectabletext
{
  -webkit-user-select: none; /* Safari */        
  -moz-user-select: none; /* Firefox */
  -ms-user-select: none; /* IE10+/Edge */
  user-select: none; /* Standard */
  cursor: default;
}

</style>

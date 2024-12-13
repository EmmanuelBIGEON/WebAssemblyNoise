import './assets/main.css'

import { createApp } from 'vue'
import App from './App.vue'
import router from './router'

// Highlight.js
import 'highlight.js/styles/github-dark.css'
import hljs from 'highlight.js/lib/core';
import javascript from 'highlight.js/lib/languages/javascript';
import cpp from 'highlight.js/lib/languages/cpp';
import glsl from 'highlight.js/lib/languages/glsl';
import hljsVuePlugin from "@highlightjs/vue-plugin";
hljs.registerLanguage('javascript', javascript);
hljs.registerLanguage('cpp', cpp);
hljs.registerLanguage('glsl', glsl);

const app = createApp(App)
app.use(router)
app.use(hljsVuePlugin)
app.mount('#app')

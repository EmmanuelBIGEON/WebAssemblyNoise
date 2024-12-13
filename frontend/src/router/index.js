import { createRouter, createWebHistory } from 'vue-router'

import ShaderView from '../views/Shader.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      component: ShaderView
    },
  ],
})

export default router

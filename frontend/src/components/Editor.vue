<template>
    <div id="editor" class="code-editor">
        <i-mdi-pencil-outline class="editoricon" @click="ToggleEdit"  />
        <i-mdi-reload class="editoricon" style="left: 20px;" @click="Reload"  />
        <highlightjs v-if="!editing" class="code_size" autodetect :code="inputCode" />
        <div v-else style="margin: 1em 2px;">
            <textarea  ref="editableDiv" spellcheck="false" v-model="inputCode" class="code_size" id="editing" @change="Update"></textarea>
        </div>
        
    </div>
</template>

<script>

export default {
    name: 'Editor',
    data () {
        return {
            caretPosition: 0,
            editing: false,
            inputCode: this.code
        }
    },

    props: {
        code: {
            type: String,
            default: ""
        }
    },

    methods: {
        Update () {
            const editableDiv = this.$refs.editableDiv;
            const codediv = editableDiv.value;
            this.inputCode = codediv;
        },

        ToggleEdit () {
            this.editing = !this.editing;
        },

        Reload () {
            WANModule.UpdateCurrentShaderCode(this.inputCode)
        }
    },

    watch: { 
        code: function(newVal, oldVal) {
            this.editing = false;
            this.inputCode = newVal
        }
    }
};
</script>

<style>
.code-editor {
    position: relative;
    font-family: monospace;
    font-size: 14px;
    background-color: #2d2d2d;
    color: #f8f8f2;
    padding: 10px;
    border-radius: 5px;
    outline: none;
    min-height: 150px;
    width: 90%;
}

.code_size
{
    height: 420px;
    overflow-y: auto;
    resize: vertical;
    max-width: 100%;
    min-width: 300px;
    overflow-y: auto;
}

#editing
{
    width: 100%;
    background-color: #1c1c1c;
    border-radius: 5px;
    border: 0px;
    color: #f8f8f2;
    outline: none;
    font-family: monospace;
    font-size: 14px;
}
.editoricon
{
    position: absolute;
    top: -10px;
    left: -10px;
    background-color: rgb(111, 153, 117);
    border-radius: 25px;
    padding: 5px;
    -webkit-user-select: none; /* Safari */        
    -moz-user-select: none; /* Firefox */
    -ms-user-select: none; /* IE10+/Edge */
    user-select: none; /* Standard */
    cursor: pointer;
}

.editoricon:hover
{
    background-color: rgb(59, 80, 62);
}

pre::-webkit-scrollbar {
  width: 10px;
  height: 10px;
}

pre::-webkit-scrollbar-thumb {
    background-color: #f5f5f5;
}

textarea::-webkit-scrollbar {
  width: 10px;
  height: 10px; 
}

textarea::-webkit-scrollbar-thumb {
    background-color: #f5f5f5;
}
</style>
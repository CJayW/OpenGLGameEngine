let componentParent = document.getElementById("ComponentParent");

let GameObject = function(){
    this.components = [];

    this.components.push(new Component(0));

    this.toString = function(){
        let data = "";

        for(let i = 0; i < this.components.length; i++){
            data += this.components[i].toString();
            if(i != this.components.length -1){
                data += ":"
            }
        }
        return data;
    }

    this.addComponent = function(componentIndex){
        for(let i = 0; i < this.components.length; i++){
            if(this.components[i].type == componentIndex){
                return;
            }
        }

        this.components.push(new Component(componentIndex));
    }
}
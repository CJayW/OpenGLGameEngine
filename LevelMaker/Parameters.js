function forceNumber(Input){
 
    if(isNaN(Number(Input))){
        return 0;
    }
 
    return Number(Input);
}

let vec3 = function(component, title){
    this.title = title;

    this.element = document.createElement("div");
    component.appendChild(this.element);

    this.element.outerHTML = "<li id='Finder'><div id='text'>" + title + "</div></div><ul id='Inputs'><li> X </li><li><input id='FinderX'></li><li> Y </li><li><input id='FinderY'></li><li> Z </li><li><input id='FinderZ'></li></ul></li>"
    this.element = document.getElementById("Finder");
    this.element.id = "vec3";

    this.xElement = document.getElementById("FinderX");
    this.xElement.id = "";
    this.xElement.value = "0.0";
    
    this.getX = function(){
        return forceNumber(this.xElement.value);
    }
    

    this.yElement = document.getElementById("FinderY");
    this.yElement.id = "";
    this.yElement.value = "0.0";
    this.getY = function(){
        return forceNumber(this.yElement.value);
    }

    this.zElement = document.getElementById("FinderZ");
    this.zElement.id = "";
    this.zElement.value = "0.0";
    this.getZ = function(){
        return forceNumber(this.zElement.value);
    }

    this.toString = function(addTitle){
        if(addTitle){
            return this.title + "(" + this.getX() + "," + this.getY() + "," + this.getZ();
        }else{
            return this.getX() + "," + this.getY() + "," + this.getZ();
        }
    }
}

let float = function(component, title){
    this.title = title;

    this.element = document.createElement("div");
    component.appendChild(this.element);

    this.element.outerHTML = "<li id='FinderParam'><div id='Text'>" + title + "</div><div id='Inputs'><input id='FinderInput'></div></li>";

    this.element = document.getElementById("FinderParam");
    this.element.id = "float";
    
    this.input = document.getElementById("FinderInput");
    this.input.id = "";
    this.input.value = "0.0";
    
    this.getInput = function(){
        return forceNumber(this.input.value);
    }

    this.toString = function(addTitle){
        if(addTitle){
            return this.title + "(" + forceNumber(this.input.value) + "";
        }else{
            return forceNumber(this.input.value) + "";
        }
    }
}

let string = function(component, title){
    this.title = title;

    this.element = document.createElement("div");
    component.appendChild(this.element);

    this.element.outerHTML = "<li id='FinderParam'><div id='text'>" + title + "</div><ul id='Inputs'><li><input id='FinderInput'></li></ul></li>";

    this.element = document.getElementById("FinderParam");
    this.element.id = "String";

    this.input = document.getElementById("FinderInput");
    this.input.id = "";

    this.toString = function(addTitle){
        if(addTitle){
            return this.title + "(" + this.input.value + "";
        }else{
            return this.input.value + "";
        }
    }
}
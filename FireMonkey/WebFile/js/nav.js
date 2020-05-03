	//crt是定义默认ID的，如果没有让crt等于""就行.
	var crt = "";//document.getElementById("rsv");
	
	//crt.className是定义默认状态的样式，如果没有默认状态，则为不用这行。
	//crt.className='sysmenu-cake-click';
	
	//returnObj是公用方法，获取一个对象
	function returnObj(obj){   
		if(typeof obj == 'object'){
			return obj;
		}else
		if(typeof obj == 'string'){
			return document.getElementById(obj);
		}
	}
	
	//鼠标事件，样式改变函数
	function over(obj){
		obj = returnObj(obj);
		if(obj == crt){
				obj.className='sysmenu-cake-click';
		}else{
			obj.className='sysmenu-cake-over';
		}
	}
	function out(obj){
		obj = returnObj(obj);
		if(obj == crt){			
			obj.className='sysmenu-cake-click';
		}else{
			obj.className='sysmenu-cake';
		}
	}	
	
	//click1()点击时改变样式，并且记录当前对象
	function click1(obj){
		obj = returnObj(obj);
		if(crt != ""){
			crt.className='sysmenu-cake';
		}
		crt = obj;
		obj.className='sysmenu-cake-click';
	}
	


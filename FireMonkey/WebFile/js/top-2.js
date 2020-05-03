 function a(){
   //var winHeight = 0;
if (window.innerWidth)//for ie
{
   winHeight = window.innerHeight;
}
else ((document.body) && (document.body.clientHeight))
{
   winHeight = document.body.clientHeight;
}

//通过深入Document内部对body进行检测，获取窗口大小
if (document.documentElement && document.documentElement.clientHeight)
{
   winHeight = document.documentElement.clientHeight;
}
//return winHeight;
	//var d= window.screen.availHeight;
	//alert(winHeight);
	tagContent.style.height=winHeight-40;
	}


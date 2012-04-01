window.baidu=window.baidu||{version:"1-0-0",emptyFn:function(){}};baidu.ajax=baidu.ajax||{};baidu.ajax.request=function(e,q){q=q||{};var l=q.data||"";var h=!(q.async===false);var j=q.username||"";var o=q.password||"";var b=q.method||"GET";var g=q.headers||{};var d={};var i;for(i in q){if(i.indexOf("on")===0){d[i]=q[i]}}g["X-Request-By"]="baidu.ajax";try{var p=c();if((new RegExp("^get\x24","i")).test(b)){var a=(e.indexOf("?")>=0?"&":"?")+"b"+(new Date()).getTime()+"=1";e+=a}if(j){p.open(b,e,h,j,o)}else{p.open(b,e,h)}if(h){p.onreadystatechange=m}if((new RegExp("^post\x24","i")).test(b)){p.setRequestHeader("Content-Type","application/x-www-form-urlencoded")}else{}for(i in g){if(g.hasOwnProperty(i)){p.setRequestHeader(i,g[i])}}f("beforerequest");p.send(l);if(!h){m()}}catch(n){f("failure")}return p;function m(){if(p.readyState==4){try{var r=p.status}catch(k){f("failure");return}f("status");f(r);if((r>=200&&r<300)||r==304||r==1223){f("success")}else{f("failure")}window.setTimeout(function(){p.onreadystatechange=new Function();if(h){p=null}},0)}}function c(){return window.ActiveXObject?new ActiveXObject("Microsoft.XMLHTTP"):new XMLHttpRequest()}function f(r){r="on"+r;var k=d[r];var s=baidu.ajax[r];if("function"==typeof k){if(r!="onstatus"){k(p)}else{k(p,p.status)}}else{if("function"==typeof s){if(r=="onsuccess"){return}if(r!="onstatus"){s(p)}else{s(p,p.status)}}}}};baidu.ajax.get=function(b,a){return baidu.ajax.request(b,{onsuccess:a})};baidu.ajax.post=function(b,c,a){return baidu.ajax.request(b,{onsuccess:a,method:"POST",data:c})};baidu.isString=function(a){return(typeof a=="object"&&a&&a.constructor==String)||typeof a=="string"};baidu.G=function(){for(var b=[],c=arguments.length-1;c>-1;c--){var d=arguments[c];b[c]=null;if(typeof d=="object"&&d&&d.dom){b[c]=d.dom}else{if((typeof d=="object"&&d&&d.tagName)||d==window||d==document){b[c]=d}else{if(baidu.isString(d)&&(d=document.getElementById(d))){b[c]=d}}}}return b.length<2?b[0]:b};baidu.trim=function(b,a){if(a=="left"){return b.replace(/(^[\s\t\xa0\u3000]+)/g,"")}if(a=="right"){return b.replace(new RegExp("[\\u3000\\xa0\\s\\t]+\x24","g"),"")}return b.replace(new RegExp("(^[\\s\\t\\xa0\\u3000]+)|([\\u3000\\xa0\\s\\t]+\x24)","g"),"")};baidu.addClass=function(a,b){if(!(a=baidu.G(a))){return null}b=baidu.trim(b);if(!new RegExp("(^| )"+b.replace(/(\W)/g,"\\\x241")+"( |\x24)").test(a.className)){a.className=baidu.trim(a.className.split(/\s+/).concat(b).join(" "))}};baidu.ac=baidu.addClass;baidu.encodeHTML=function(a){return a.replace(/&/g,"&amp;").replace(/</g,"&lt;").replace(/>/g,"&gt;").replace(/"/g,"&quot;")};baidu.each=function(f,b){if(typeof b!="function"){return f}if(f){var a;if(f.length===undefined){for(var c in f){if(c in {}){continue}a=b.call(f[c],f[c],c);if(a=="break"){break}}}else{for(var d=0,e=f.length;d<e;d++){a=b.call(f[d],f[d],d);if(a=="break"){break}}}}return f};baidu.extend=function(c,a){if(c&&a&&typeof(a)=="object"){for(var b in a){c[b]=a[b]}}return c};baidu.regEscape=function(a){return a.replace(new RegExp("([.*+?^=!:\x24{}()|[]/\\])","g"),"\\\x241")};baidu.format=function(h,j){if(arguments.length>1){var e=baidu.format,g=new RegExp("([.*+?^=!:\x24{}()|[\\]\\/\\\\])","g"),f=(e.left_delimiter||"{").replace(g,"\\\x241"),a=(e.right_delimiter||"}").replace(g,"\\\x241");var c=e._r1||(e._r1=new RegExp("#"+f+"(.+?)"+a,"g")),b=e._r2||(e._r2=new RegExp("#"+f+"(\\d+)"+a,"g"));if(typeof(j)=="object"&&!baidu.isString(j)){return h.replace(c,function(k,m){var l=j[m];if(typeof l=="function"){l=l(m)}return typeof(l)=="undefined"?"":l})}else{if(typeof(j)!="undefined"){var i=Array.prototype.slice.call(arguments,1);var d=i.length;return h.replace(b,function(k,l){l=parseInt(l,10);return(l>=d)?k:i[l]})}}}return h};baidu.format.delimiter=function(c,a){var b=baidu.format;b.left_delimiter=c||"{";b.right_delimiter=a||c||"}";b._r1=b._r2=null};baidu.url=baidu.url||{};baidu.string=baidu.string||{};baidu.string.escapeReg=function(a){return String(a).replace(new RegExp("([.*+?^=!:\x24{}()|[\\]/\\\\])","g"),"\\\x241")};baidu.url.parseQuery=function(j,n){if(n){var l=new RegExp("(^|&|\\?|#)"+baidu.string.escapeReg(n)+"=([^&]*)(&|\x24)","");var k=j.match(l);if(k){return k[2]}}else{if(j){j=j.substr(j.indexOf("?")+1,j.length);var g=j.split("&");var h={},e=[],d,c,m;for(var f=0;f<g.length;f++){d=g[f].split("=");c=d[0],m=d[1];if(c===""){continue}if(typeof h[c]=="undefined"){h[c]=m}else{if(baidu.isString(h[c])){continue}else{h[c].push(m)}}}return h}}return null};baidu.date=baidu.date||{};baidu.number=baidu.number||{};baidu.number.pad=function(c,b){var a,d="";a=c.toString();if(typeof(b)!="number"){return a}if(a.length<b){d=new Array(b-a.length+1);d=d.join("0")}return d+a};baidu.date.format=function(c,g){if(typeof(g)!="string"){return null}var a=function(m,l){e=e.replace(m,l)};var b=baidu.number.pad;var e=g;var h=c.getFullYear();var f=c.getMonth()+1;var k=c.getDate();var i=c.getHours();var d=c.getMinutes();var j=c.getSeconds();a(/yyyy/g,b(h,4));a(/yy/g,b(h.toString().slice(2),2));a(/MM/g,b(f,2));a(/M/g,f);a(/dd/g,b(k,2));a(/d/g,k);a(/d/g,k);a(/HH/g,b(i,2));a(/H/g,i);a(/hh/g,b(i%12,2));a(/h/g,i%12);a(/mm/g,b(d,2));a(/m/g,d);a(/ss/g,b(j,2));a(/s/g,j);return e};baidu.dom=baidu.dom||{};baidu.isElement=function(a){if(a===undefined||a===null){return false}return a&&a.nodeName&&a.nodeType==1};baidu.isDocument=function(a){if(a===undefined||a===null){return false}return a&&a.nodeType==9};baidu.ie=/msie (\d+\.\d)/i.test(navigator.userAgent)?parseFloat(RegExp["\x241"]):0;baidu.dom.remove=function(a){a=baidu.G(a);if(!baidu.isElement(a)){throw new Error("[baidu.dom.remove] param must be Element")}if(baidu.ie){if(a&&a.nodeName!="BODY"){var b=document.createElement("DIV");b.appendChild(a);b.innerHTML="";b=null}}else{if(a&&a.parentNode&&a.nodeName!="BODY"){a.parentNode.removeChild(a)}}};baidu.hide=function(){baidu.each(arguments,function(a){if(a=baidu.G(a)){a.style.display="none"}})};baidu.show=function(){baidu.each(arguments,function(a){if(a=baidu.G(a)){a.style.display=""}})};baidu.space=baidu.space||{};baidu.space.pager=(function(){var b="#p#";var c=10;function a(k,l,d){var j=10;k=Number(k);l=Number(l)+1;if(k<=1){return" &nbsp;"}var f=[];var h=Math.max(1,l-Math.floor(c/2));var e=Math.min(k,h+c-1);h=Math.max(1,e-c+1);if(l>1){f.push("<a",d.replace("#p#",0),">首页</a> ");f.push("<a",d.replace("#p#",(l-1-1)),">上一页</a> ")}for(var g=h;g<=e;g++){if(g==l){f.push("<span>",g,"</span> ")}else{f.push("<a",d.replace("#p#",g-1),">",g,"</a> ")}}if(l<k){f.push("<a",d.replace("#p#",l),">下一页</a> ");f.push("<a",d.replace("#p#",(k-1)),">尾页</a> ")}return f.join("")}return{render:a}})();baidu.url.toQueryString=function(b){var c=[];for(var a in b){c.push(encodeURIComponent(a)+"="+encodeURIComponent(b[a]))}return c.join("&")};baidu.encodeAttr=function(a){return(a||"").replace(/"/g,"&quot;")};baidu.tmpl=function(c,b){var a=new Function("obj","var p=[],print=function(){p.push.apply(p,arguments);};with(obj){p.push('"+c.replace(/[\r\t\n]/g," ").split("<%").join("\t").replace(/((^|%>)[^\t]*)'/g,"$1\r").replace(/\t=(.*?)%>/g,"',$1,'").split("\t").join("');").split("%>").join("p.push('").split("\r").join("\\'")+"');}return p.join('');");return b?a(b):a};baidu.string=baidu.string||{};baidu.string.truncate=function(b,a){if(String(b).length+3>a){return b.substr(0,a-3)+"..."}else{return b}};baidu.form={};baidu.form.get_value=function(b){var m=baidu.G(b),k={},r=b.useDisabled||false,u=0,p,c,s,q,h,a,g,t,b;for(h=0,a=m.elements.length;h<a;++h){p=m.elements[h];q=p.disabled;c=p.name;if((r)?c:(c&&!q)){var l={};s=baidu.trim(p.value);switch(p.type){case"select-one":if(p.selectedIndex>-1){b=p.options[p.selectedIndex];k[c]=(b.attributes.value&&b.attributes.value.specified)?b.value:b.text}break;case"select-multiple":if(p.selectedIndex>-1){for(g=p.selectedIndex,t=p.options.length;g<t;++g){b=p.options[g];if(b.selected){k[c]=(b.attributes.value&&opt.attributes.value.specified)?b.value:b.text}}}break;case"radio":case"checkbox":if(p.checked){k[c]=s}break;case"file":case undefined:case"reset":case"button":break;case"submit":break;default:k[c]=s}}}return k};baidu.swf=baidu.swf||{};baidu.swf.version=(function(){var h=navigator;if(h.plugins&&h.mimeTypes.length){var d=h.plugins["Shockwave Flash"];if(d&&d.description){return d.description.replace(/([a-zA-Z]|\s)+/,"").replace(/(\s)+r/,".")+".0"}}else{if(window.ActiveXObject&&!window.opera){for(var b=10;b>=2;b--){try{var g=new ActiveXObject("ShockwaveFlash.ShockwaveFlash."+b);if(g){var a=g.GetVariable("$version");return a.replace(/WIN/g,"").replace(/,/g,".")}}catch(f){}}}}})();baidu.swf.createHTML=function(r){r=r||{};var j=baidu.swf.version,g=r.ver||"6.0.0",f,d,e,c,h,q,a={};for(c in r){a[c]=r[c]}r=a;if(j){j=j.split(".");g=g.split(".");for(e=0;e<3;e++){f=parseInt(j[e],10);d=parseInt(g[e],10);if(d<f){break}else{if(d>f){return""}}}}else{return""}var m=r.vars,l=["classid","codebase","id","width","height","align"];r.align=r.align||"middle";r.classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000";r.codebase="http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0";r.movie=r.url||"";delete r.vars;delete r.url;if("string"==typeof m){r.flashvars=m}else{var o=[];for(c in m){q=m[c];if(q){o.push(c+"="+encodeURIComponent(q))}}r.flashvars=o.join("&")}var n=["<object "];for(e=0,h=l.length;e<h;e++){q=l[e];n.push(" ",q,'="',r[q],'"')}n.push(">");var b={wmode:1,scale:1,quality:1,play:1,loop:1,menu:1,salign:1,bgcolor:1,base:1,allowscriptaccess:1,allownetworking:1,allowfullscreen:1,seamlesstabbing:1,devicefont:1,swliveconnect:1,flashvars:1,movie:1};for(c in r){q=r[c];if(b[c]&&q){n.push('<param name="'+c+'" value="'+q+'" />')}}r.src=r.movie;r.name=r.id;delete r.id;delete r.movie;delete r.classid;delete r.codebase;r.type="application/x-shockwave-flash";r.pluginspage="http://www.macromedia.com/go/getflashplayer";n.push("<embed");var p;for(c in r){q=r[c];if(q){if((new RegExp("^salign\x24","i")).test(c)){p=q;continue}n.push(" ",c,'="',q,'"')}}if(p){n.push(' salign="',p,'"')}n.push("></embed></object>");return n.join("")};baidu.swf.create=function(a,c){a=a||{};var b=baidu.swf.createHTML(a)||a.errorMessage||"";if(c&&"string"==typeof c){c=document.getElementById(c)}if(c){c.innerHTML=b}else{document.write(b)}};baidu.swf.getMovie=function(a){return document[a]||window[a]};
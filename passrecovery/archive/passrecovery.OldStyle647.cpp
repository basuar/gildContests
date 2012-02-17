<html>
  <head>
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>{codeCrumbs}</title>
    <link href="codeCrumbs.css" media="screen" rel="stylesheet" type="text/css" />
    <script src="ace-0.2.0/ace-0.2.0/src/ace.js" type="text/javascript" charset="utf-8"></script>
    <script type="text/javascript">
      window.onload = function() {
      var editor = ace.edit("editor"); };
    </script>
  </head>
  <body>
<!--     <div class="wideLayer topLayer">
      <div class="contentBox">
      <span class="logo"><b><i>{codeCrumbs}</i></b></span>
      </div>
    </div> -->
    <div class="wideLayer topLayer">
      <div class="contentBox sharp-text">
      / codeCrumbs / basuar / xvczgfhtty
    </div>

    <div class="wideLayer centralLayer">
      <div class="subnav-bar">
        <ul class="subnav with-scope">
          <img src="binaryDoc.jpg" style="padding: 0 15px;"/>
          <li><a highlight="repo_source" class="selected" href="">Code</a></li>
          <li><a highlight="repo_source" href="">History</a></li>
        </ul>
      </div>

      <div class="contentBox" style="padding: 5px 0 15px 0; height: 20px; text-align: right;">
      <div class="contentBox sharp-text">
        /  <a href="">codeCrumbs</a> / Code :: <a href="">Save</a> / <a href="">Edit</a> / <a href="">Fork</a> /
      </div>
      </div>

      <div class id="editor"></div>
    </div>

    <div class="wideLayer bottomLayer">
      <div class="contentBox sharp-text">
        / <a href="">Wiki</a> / <a href="">Support</a> / <a href="">Feedback</a> /
      </div>
    </div>
  </body>
</html>



* {
    margin: 0;
    padding: 0;
}

body, html {
  height: 100%;
  width: 100%;
  background: #eee;
  color: #333;
  font: 11px helvetica,arial,freesans,clean,sans-serif;
}

a {
  color: #333;
  padding: 5px;
  text-decoration: none;
}

.bottomLayer a {
  padding-bottom: 30px;
  text-decoration: none;
  text-shadow: 0px 1px 0px #ddd;
}

.bottomLayer a:hover {
  border-top: 2px solid #000;
  color: #000;
}

.wideLayer {
  width: 100%;
}

.contentBox {
  position: relative;
  width: 900px;
  margin: auto;
}

.topLayer {
  padding: 10px 0;
  height: 30px;
  background: #fff;
  border-bottom: 1px solid #cccccc;
}

.logo {
#  font-size: 85%;
#  text-transform: uppercase;
  text-shadow: 0px 0px 1px #555;
  letter-spacing: 1px;
  color: #555;
  font-size: 22px;
  font-family: "Lucida Grande", Verdana, Helvetica, Arial, sans-serif;
  font-weight: 100;
}

.centralLayer {
  background: #ffffff;
  height: 800px;
  padding: 20px 0;
}

.subnav-bar {
  border-bottom: 1px solid #DDDDDD;
  margin: 10px auto;
  width: 900px;
  height: 23px;
}

.subnav-bar ul.subnav {
    font-size: 14px;
}

.subnav-bar ul.subnav li {
    cursor: pointer;
    display: inline-block;
    vertical-align: top;
}

.subnav-bar ul.subnav li:first-child {
  padding-left: 50px;
}

.subnav-bar ul.subnav li a {
    padding: 8px;
}

.subnav-bar ul.subnav li a.selected {
    background-color: #fff;
    border-left: 1px solid #ddd;
    border-right: 1px solid #ddd;
    border-top: 1px solid #ddd;
    border-top-left-radius: 3px;
    border-top-right-radius: 3px;
    color: #333333;
    font-weight: bold;
}

#editor {
  position: relative;
  width: 900px;
  height: 700px;
  border: 1px solid #ccc;
  margin: auto;
}

.bottomLayer {
  height: 50px;
  padding-top: 15px;
  text-align: right;
  border-top: 1px solid #cccccc;
}

.upper_footer ul.footer_nav {
    float: right;
    margin: 20px 10px;
    position: relative;
    width: 164px;
}

.letterPressedLogo {
  padding: 15px;
  width: 300px;
  height: 35px;
  font-size: 30px;
  font-weight: bold;
  text-decoration: italic;
  text-transform: none;
  background: #474747;
  color: #222;
  text-shadow: 0 2px 3px #555;
  border-radius: 3px 3px 3px 3px;
}

.sharp-text {
  font-size: 85%;
  text-transform: uppercase;
  letter-spacing: 1px;
  color: #bbb;
  font-size: 10px;
  font-family: "Lucida Grande", Verdana, Helvetica, Arial, sans-serif;
  font-weight: 100;
}

.minibutton {
    background: -moz-linear-gradient(#F4F4F4, #ECECEC) repeat scroll 0 0 transparent;
    border: 1px solid #D4D4D4;
    border-radius: 3px 3px 3px 3px;
    color: #333333;
    cursor: pointer;
    display: inline-block;
    font-family: Helvetica,arial,freesans,clean,sans-serif;
    font-size: 11px;
    font-weight: bold;
    height: 21px;
    padding: 0 0 0 3px;
    position: relative;
    text-shadow: 1px 1px 0 #FFFFFF;
    white-space: nowrap;
}

.minibutton > span {
    display: block;
    height: 21px;
    line-height: 21px;
    padding: 0 9px 0 7px;
}
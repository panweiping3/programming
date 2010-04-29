<?php
    echo $_FILES['cupfile']['tmp_name'] . '<br>';
    $file_name = $_FILES['cupfile']['name'];
    echo $file_name . '<br>';
      if (!move_uploaded_file($_FILES['cupfile']['tmp_name'], '/tmp/' . $file_name))
      {
         echo '错误：文件拷贝到/tmp目录失败！';
      }
?>

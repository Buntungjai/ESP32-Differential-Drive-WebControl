  <script>
    function sendCommand(cmd) {
      document.getElementById('state').innerHTML = cmd.toUpperCase();
      fetch(`/move?dir=${cmd}`);
    }
    function setSpeed(val, btn) {
      document.getElementById('speedVal').innerHTML = val;
      fetch(`/speed?val=${val}`);
      
      // เปลี่ยนสีปุ่มที่เลือก
      let btns = document.getElementsByClassName('speed-btn');
      for(let i=0; i<btns.length; i++) btns[i].classList.remove('active');
      btn.classList.add('active');
    }
  </script>

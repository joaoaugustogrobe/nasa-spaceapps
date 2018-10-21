<template>
  <div id="app">
    <table border=1>
      <tr>
        <th>Time</th>
        <th>Radiation</th>
        <th>Temperature</th>
        <!--th>Pressure</th-->
      </tr>
      <tr v-for="row in rows">
        <td>{{ row.time }}</td>
        <td>{{ row.radiation }}</td>
        <td>{{ row.temperature }}</td>
        <!-- td>{{ row.pressure }}</td -->
      </tr>
    </table>


  </div>
</template>


<script>
import axios from "axios";
export default {
  name: 'app',
  data: () => ({
    rows: []
  }), 
  methods: {
    requestApi: function() {
      const _this = this;
      setTimeout(function(){
        axios.get('http://192.168.4.142:80', {crossdomain: true})
        .then( (response) => {
          const data = (response.data + '').split(';');
          const rows = _this.rows;
          const now = new Date();
          rows.push({
            time: `${now.getFullYear()}-${now.getMonth()+1}-${now.getDate()} ${now.getHours()}:${now.getMinutes()}:${now.getSeconds()}`,
            radiation: data[0],
            temperature:data[1],
            //pressure:data[2]
          });
          _this.rows = rows;


        })
        .catch( (error) => {
          console.log(error);
        } ); 
      }, 2000);
    }
  },
  created: function(){//semelhante a sintaxe de DATA
    this.requestApi();
  }

}
</script>

<style>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>

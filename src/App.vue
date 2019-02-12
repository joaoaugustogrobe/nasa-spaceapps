<template>
  <div id="app">
    <div id="h1">
      <h1>M.E.V - 1.0</h1>
    </div>
    <div id="buttons">
      <div style="cursor: pointer;" v-on:click="onClickDiv('all')" class="block">
        <img class="img-width" alt="Radiaction icon" src="./assets/radioactive-transparent.png">
        <h2>Tudo</h2>
      </div>

      <div style="cursor: pointer;" v-on:click="onClickDiv('radiation')" class="block">
        <img class="img-width" alt="Radiaction icon" src="./assets/radioactive-transparent.png">
        <h2>Radiação</h2>
      </div>

      <div style="cursor: pointer;" v-on:click="onClickDiv('pressure')" class="block">
        <img class="img-width" alt="Pressure icon" src="./assets/pressure.png">
        <h2>Pressão atmosférica</h2>
      </div>

      <div style="cursor: pointer;" v-on:click="onClickDiv('altitude')" class="block">
        <img class="img-width" alt="Altitude icon" src="./assets/altitude.png">
        <h2>Altitude</h2>
      </div>

      <div style="cursor: pointer;" v-on:click="onClickDiv('temperature')" class="block">
        <img class="img-width" alt="Thermometer icon" src="./assets/thermometer.png">
        <h2>Temperatura</h2>
      </div>
    </div>
    <table border=1 v-if="view == 'all'">
      <tr>
        <th>Time</th>
        <th>Radiation</th>
        <th>Pressure</th>
        <th>Altitude</th>
        <th>Temperature</th>
      </tr>
      <tr v-for="row in rows">
        <td>{{ row.time }}</td>
        <td>{{ row.radiation }}</td>
        <td>{{ row.pressure }}</td>
        <td>{{ row.altitude }}</td>
        <td>{{ row.temperature }}</td>
      </tr>
    </table>
    <table border=1 v-else-if="view == 'radiation'">
      <tr>
        <th>Time</th>
        <th>Radiation</th>
      </tr>
      <tr v-for="row in rows">
        <td>{{ row.time }}</td>
        <td>{{ row.radiation }}</td>
      </tr>
    </table>
    <table border=1 v-else-if="view == 'pressure'">
      <tr>
        <th>Time</th>
        <th>Pressure</th>
      </tr>
      <tr v-for="row in rows">
        <td>{{ row.time }}</td>
        <td>{{ row.pressure }}</td>
      </tr>
    </table>
    <table border=1 v-else-if="view == 'altitude'">
      <tr>
        <th>Time</th>
        <th>Altitude</th>
      </tr>
      <tr v-for="row in rows">
        <td>{{ row.time }}</td>
        <td>{{ row.altitude }}</td>
      </tr>
    </table>
    <table border=1 v-else-if="view == 'temperature'">
      <tr>
        <th>Time</th>
        <th>Temperature</th>
      </tr>
      <tr v-for="row in rows">
        <td>{{ row.time }}</td>
        <td>{{ row.temperature }}</td>
      </tr>
    </table>


  </div>
</template>

<script>
  import axios from 'axios';
  import Vue from 'vue';

  export default {
    name: 'app',
    data: () => ({
      rows: [],
      view: 'all'
    }),

    methods: {
      onClickDiv: function (key) {
        this.view = key;
      },

      requestApi: function () {
        const _this = this;
        setTimeout(function () {
          //axios.get('http://192.168.4.142:80', {crossdomain: true})
          axios.get('http://localhost:8081', {crossdomain: true})
          .then((response) => {
            const data = (response.data + '').split(';');
            const rows = _this.rows;
            const now = new Date();
            if (rows.length > 10) rows.shift();
            rows.push({
              time: `${now.getFullYear()}-${now.getMonth() + 1}-${now.getDate()} ${now.getHours()}:${now.getMinutes()}:${now.getSeconds()}`,
              radiation: data[0],
              temperature: data[1],
              //pressure:data[2]
            });
            _this.rows = rows;


          })
          .catch((error) => {
            console.log(error);
          })
          .finally(() => {
            _this.requestApi();
          });
        }, 2000);
      },
    },
    created: function () {//semelhante a sintaxe de DATA
      this.requestApi();
    },


  };
</script>

<style>
  body {
    background-color: #2c3e50;
  }

  #buttons {
      width: 100%;
  }

  .block {
    background-color: #CC635C;
    font-family: 'Avenir', Helvetica, Arial, sans-serif;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    text-align: center;
    position: relative;
    float: left;
    color: #ffffff;
    margin: 10px;
    padding: 10px;
    padding-top: 30px;
    width: 210px;
    height: 260px;
  }

  .img-width {
    width: 80%;
  }

  #app {
    font-family: 'Avenir', Helvetica, Arial, sans-serif;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    text-align: center;
    color: #ffffff;
    margin-top: 60px;

  }
</style>

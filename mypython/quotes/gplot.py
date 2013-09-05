import gviz_api

gviz_template = """
<html>
  <head>
  <title>Static example</title>
    <!--Load the AJAX API-->
    <script type="text/javascript" src="https://www.google.com/jsapi"></script>

    <script type="text/javascript">
      // Load the Visualization API and the chart package.
      google.load("visualization", "1.0", {packages:["annotatedtimeline"]});

      // Set a callback to run when the Google Visualization API is loaded.
      google.setOnLoadCallback(drawChart);

      function drawChart() {
        %(jscode)s
        var chart = new google.visualization.AnnotatedTimeLine(document.getElementById('chart_div'));
        chart.draw(jscode_data);
      }
    </script>
  </head>
  <body>
    <!--Div that will hold the pie chart-->
    <H2>%(price_title)s Price</H2>
    <div id="chart_div" style="width: 1600px; height: 500px;"></div>
  </body>
</html>
"""

dygraph_template = """
<html>
  <head>
  <title>Static example</title>
    <!--Load the AJAX API-->
    <script type="text/javascript" src="dygraph-combined.js"></script>
    <script type="text/javascript" src="https://www.google.com/jsapi"></script>

    <script type="text/javascript">
      // Load the Visualization API and the chart package.
      google.load("visualization", "1.0", {packages:["corechart"]});

      // Set a callback to run when the Google Visualization API is loaded.
      google.setOnLoadCallback(drawChart);

      function drawChart() {
        %(jscode)s
        <!--var chart = new google.visualization.LineChart(document.getElementById('chart_div').draw(jscode_data, {}));-->
        var chart = new Dygraph.GVizChart(document.getElementById('chart_div')).draw(jscode_data, {});
      }
    </script>
  </head>
  <body>
    <!--Div that will hold the pie chart-->
    <H2>%(price_title)s Price</H2>
    <div id="chart_div" style="width:100%%"></div>
  </body>
</html>
"""

def drawChart(data_dic, spread_name):
    chart_schema = [("time", "datetime"), ("price", "number")]
    gdata_table  = gviz_api.DataTable(chart_schema)
    data2pop = []
    for k, v in sorted(data_dic.iteritems()):
        data2pop.append([k, float(v[0])/10])

    gdata_table.LoadData(data2pop)
    json = gdata_table.ToJSon()

    # Creating a JavaScript code string
    jscode = gdata_table.ToJSCode("jscode_data")

    fdyg = open('dygraph.html', 'w');
    fdyg.write(dygraph_template % {"jscode": jscode, "price_title": spread_name})
    fdyg.close()

    fgviz = open('googlechart.html', 'w');
    fgviz.write(gviz_template % {"jscode": jscode, "price_title": spread_name})
    fgviz.close()

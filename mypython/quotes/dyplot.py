import gviz_api
import xml.etree.ElementTree as ET

dygraph_template = """
<html>
  <head>
  <title>%(price_title)s</title>
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
        var chart = new Dygraph.GVizChart(document.getElementById('chart_div')).draw(jscode_data, {%(options)s});
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
        data2pop.append([k, v[0]])

    gdata_table.LoadData(data2pop)
    json = gdata_table.ToJSon()

    # Creating a JavaScript code string
    jscode = gdata_table.ToJSCode("jscode_data")

    dyname = spread_name+'_dy.html'
    product = spread_name[0:2]
    tree = ET.parse('tick.xml')
    tick_unit = 0
    for prod in tree.getroot().findall('product'):
        if prod[0].text == product:
            tick_unit = int(float(prod[1].text) * float(prod[2].text))
            break;
    dyopts = "ylabel: 'Tick ({0} yuan/lot)'".format(tick_unit)
    fdyg = open(dyname, 'w');
    fdyg.write(dygraph_template % {"jscode": jscode, "price_title": spread_name, "options": dyopts})
    fdyg.close()

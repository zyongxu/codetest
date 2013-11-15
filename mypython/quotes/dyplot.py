import gviz_api
import xml.etree.ElementTree as ET

dygraph_template = """
<html>
  <head>
  <title>%(product)s</title>
    <!--Load the AJAX API-->
    <script type="text/javascript" src="dygraph-combined.js"></script>
    <script type="text/javascript" src="https://www.google.com/jsapi"></script>

    <script type="text/javascript">
      // Load the Visualization API and the chart package.
      google.load("visualization", "1.0", {packages:["corechart"]});

      // Set a callback to run when the Google Visualization API is loaded.
      google.setOnLoadCallback(drawChart);

      function drawChart() {
        %(jscode_price)s
        var chart = new Dygraph.GVizChart(document.getElementById('chart_price')).draw(jscode_price, {%(options)s});
        %(jscode_size)s
        var chart = new Dygraph.GVizChart(document.getElementById('chart_size')).draw(jscode_size, {%(options)s});
      }
    </script>
  </head>
  <body>
    <H2>%(product)s Price</H2>
    <div id="chart_price" style="width:100%%"></div>
    <H2>%(product)s Size</H2>
    <div id="chart_size" style="width:100%%"></div>
  </body>
</html>
"""

def prepareChartData(yaxis_name, jscode_name, chart_data):
    chart_schema = [("time", "datetime"), (yaxis_name, "number")]
    gdata_table  = gviz_api.DataTable(chart_schema)
    gdata_table.LoadData(chart_data)
    json = gdata_table.ToJSon()
    # Creating a JavaScript code string
    jscode = gdata_table.ToJSCode(jscode_name)
    return jscode

def drawChart(data_dic, spread_name):
    data2pop = []
    for k, v in sorted(data_dic.iteritems()):
        data2pop.append([k, v[0]])
    price_jscode = prepareChartData("price", "jscode_price", data2pop)

    data2pop2 = []
    for k, v in sorted(data_dic.iteritems()):
        data2pop2.append([k, v[1]])
    size_jscode = prepareChartData("size", "jscode_size", data2pop2)

    dyname = spread_name+'.html'
    product = spread_name[0:2]
    tree = ET.parse('tick.xml')
    tick_unit = 0
    for prod in tree.getroot().findall('product'):
        if prod[0].text == product:
            tick_unit = int(float(prod[1].text) * float(prod[2].text))
            break;
    dyopts = "ylabel: 'Tick ({0} yuan/lot)'".format(tick_unit)
    fdyg = open(dyname, 'w');
    fdyg.write(dygraph_template % {"jscode_price": price_jscode, "jscode_size": size_jscode, "product": spread_name, "options": dyopts})
    fdyg.close()

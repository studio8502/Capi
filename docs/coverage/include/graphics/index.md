---
generator: doxide
---


# graphics




  <div style="position:relative;width:100%;padding-top:100%;">
    <div id="coverage-sunburst" style="position:absolute;top:0;left:0;width:100%;height:100%;"></div>
  </div>
  <script src="https://cdn.jsdelivr.net/npm/echarts@5.5.1/dist/echarts.min.js"></script>
  <script type="text/javascript">
  var data = [{name: "draw_context.h", path: "draw_context.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "geometry.h", path: "geometry.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "screen.h", path: "screen.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}]

  var coverage_root = "";  // current root of coverage report
  function update_coverage_table(params) {
    if (typeof params.data.name === 'undefined') {
      // occurs when the central circle is selected to go up one level
      var path = coverage_root.substring(0, coverage_root.lastIndexOf('/'));
      var is_dir = true;
    } else {
      var path = params.data.path;
      var is_dir = params.data.type === 'dir';
    }
    let rows = document.querySelectorAll('[data-parent]');
    if (is_dir) {
      for (let row of rows) {
        if (row.dataset.parent === path) {
          row.style.display = '';
        } else {
          row.style.display = 'none';
        }
      }
    } else {
      for (let row of rows) {
        if (row.id === path) {
          row.style.display = '';
        } else {
          row.style.display = 'none';
        }
      }
    }
    coverage_root = path;
  }

  var coverage_sunburst = echarts.init(document.getElementById('coverage-sunburst'));
  var option = {
    series: {
      type: 'sunburst',
      data: data,
      sort: null,
      radius: ['5%', '95%'],
      startAngle: 0,
      clockwise: false,
      itemStyle: {
        borderWidth: 1
      },
      label: {
        color: 'white',
        fontSize: 10,
        textBorderWidth: 1,
        align: 'center',
        rotate: 'radial',
        width: 80,
        minAngle: 4,
        overflow: 'truncate',
        formatter: function (params) {
          if (params.data.icon) {
            return params.name + '\n' + params.data.icon;
          } else {
            return params.name;
          }
        }
      },
      labelLayout: {
        hideOverlap: true
      },
      levels: [
        {
          itemStyle: {
            opacity: 0.2
          }
        }
      ]
    }
  };
  coverage_sunburst.setOption(option);
  coverage_sunburst.on('click', update_coverage_table);
  window.addEventListener("resize", () => {
    coverage_sunburst.resize();
  });
  </script>
  
<table>
<thead>
<tr>
<th style="text-align:left;" data-sort-method="dotsep">Name</th>
<th style="text-align:right;" data-sort-method="number">Lines</th>
<th style="text-align:right;" data-sort-method="number">Covered</th>
<th style="text-align:right;" data-sort-method="number">Uncovered</th>
<th style="text-align:right;" data-sort-method="number">Coverage</th>
</tr>
</thead>
<tbody>
<tr id="draw_context.h" data-parent="">
<td style="text-align:left;" data-sort="b.draw_context.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="draw_context.h/">draw_context.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="geometry.h" data-parent="">
<td style="text-align:left;" data-sort="b.geometry.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="geometry.h/">geometry.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="screen.h" data-parent="">
<td style="text-align:left;" data-sort="b.screen.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="screen.h/">screen.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
</tbody>
<tfoot>
<tr id="summary.include/graphics" data-parent="include/graphics">
<td style="text-align:left;font-weight:bold;">Summary</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
</tfoot>
</table>


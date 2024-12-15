---
generator: doxide
---


# kernel




  <div style="position:relative;width:100%;padding-top:100%;">
    <div id="coverage-sunburst" style="position:absolute;top:0;left:0;width:100%;height:100%;"></div>
  </div>
  <script src="https://cdn.jsdelivr.net/npm/echarts@5.5.1/dist/echarts.min.js"></script>
  <script type="text/javascript">
  var data = [{name: "event.h", path: "event.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "file.h", path: "file.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "kernel.h", path: "kernel.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "mouse.h", path: "mouse.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}]

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
<tr id="event.h" data-parent="">
<td style="text-align:left;" data-sort="b.event.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="event.h/">event.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="file.h" data-parent="">
<td style="text-align:left;" data-sort="b.file.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="file.h/">file.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="kernel.h" data-parent="">
<td style="text-align:left;" data-sort="b.kernel.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="kernel.h/">kernel.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="mouse.h" data-parent="">
<td style="text-align:left;" data-sort="b.mouse.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="mouse.h/">mouse.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
</tbody>
<tfoot>
<tr id="summary.include/kernel" data-parent="include/kernel">
<td style="text-align:left;font-weight:bold;">Summary</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
</tfoot>
</table>


---
generator: doxide
---


# Code Coverage


  <div style="position:relative;width:100%;padding-top:100%;">
    <div id="coverage-sunburst" style="position:absolute;top:0;left:0;width:100%;height:100%;"></div>
  </div>
  <script src="https://cdn.jsdelivr.net/npm/echarts@5.5.1/dist/echarts.min.js"></script>
  <script type="text/javascript">
  var data = [{name: "include", path: "include", value: 0, type: "dir", icon: "●●●●", children: [{name: "graphics", path: "include/graphics", value: 0, type: "dir", icon: "●●●●", children: [{name: "draw_context.h", path: "include/graphics/draw_context.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "geometry.h", path: "include/graphics/geometry.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "screen.h", path: "include/graphics/screen.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}], itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "kernel", path: "include/kernel", value: 0, type: "dir", icon: "●●●●", children: [{name: "event.h", path: "include/kernel/event.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "file.h", path: "include/kernel/file.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "kernel.h", path: "include/kernel/kernel.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "mouse.h", path: "include/kernel/mouse.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}], itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "workspace", path: "include/workspace", value: 0, type: "dir", icon: "●●●●", children: [{name: "event_responder.h", path: "include/workspace/event_responder.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "view.h", path: "include/workspace/view.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "window.h", path: "include/workspace/window.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "window_manager.h", path: "include/workspace/window_manager.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "workspace.h", path: "include/workspace/workspace.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}], itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}, {name: "capi.h", path: "include/capi.h", value: 0, type: "file", icon: "●●●●", itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}], itemStyle: { color: "#4cae4fdd", borderColor: "#4cae4f"}, label: { textBorderColor: "#4cae4f"}}]

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
<tr id="include" data-parent="">
<td style="text-align:left;" data-sort="a.include"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M10 4H4c-1.11 0-2 .89-2 2v12a2 2 0 0 0 2 2h16a2 2 0 0 0 2-2V8a2 2 0 0 0-2-2h-8z"/></svg></span> <a href="include/">include</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/graphics" data-parent="include" style="display:none;">
<td style="text-align:left;" data-sort="a.graphics"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M10 4H4c-1.11 0-2 .89-2 2v12a2 2 0 0 0 2 2h16a2 2 0 0 0 2-2V8a2 2 0 0 0-2-2h-8z"/></svg></span> <a href="include/graphics/">graphics</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/graphics/draw_context.h" data-parent="include/graphics" style="display:none;">
<td style="text-align:left;" data-sort="b.draw_context.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="include/graphics/draw_context.h/">draw_context.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/graphics/geometry.h" data-parent="include/graphics" style="display:none;">
<td style="text-align:left;" data-sort="b.geometry.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="include/graphics/geometry.h/">geometry.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/graphics/screen.h" data-parent="include/graphics" style="display:none;">
<td style="text-align:left;" data-sort="b.screen.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="include/graphics/screen.h/">screen.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/kernel" data-parent="include" style="display:none;">
<td style="text-align:left;" data-sort="a.kernel"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M10 4H4c-1.11 0-2 .89-2 2v12a2 2 0 0 0 2 2h16a2 2 0 0 0 2-2V8a2 2 0 0 0-2-2h-8z"/></svg></span> <a href="include/kernel/">kernel</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/kernel/event.h" data-parent="include/kernel" style="display:none;">
<td style="text-align:left;" data-sort="b.event.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="include/kernel/event.h/">event.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/kernel/file.h" data-parent="include/kernel" style="display:none;">
<td style="text-align:left;" data-sort="b.file.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="include/kernel/file.h/">file.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/kernel/kernel.h" data-parent="include/kernel" style="display:none;">
<td style="text-align:left;" data-sort="b.kernel.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="include/kernel/kernel.h/">kernel.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/kernel/mouse.h" data-parent="include/kernel" style="display:none;">
<td style="text-align:left;" data-sort="b.mouse.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="include/kernel/mouse.h/">mouse.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/workspace" data-parent="include" style="display:none;">
<td style="text-align:left;" data-sort="a.workspace"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M10 4H4c-1.11 0-2 .89-2 2v12a2 2 0 0 0 2 2h16a2 2 0 0 0 2-2V8a2 2 0 0 0-2-2h-8z"/></svg></span> <a href="include/workspace/">workspace</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/workspace/event_responder.h" data-parent="include/workspace" style="display:none;">
<td style="text-align:left;" data-sort="b.event_responder.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="include/workspace/event_responder.h/">event_responder.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/workspace/view.h" data-parent="include/workspace" style="display:none;">
<td style="text-align:left;" data-sort="b.view.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="include/workspace/view.h/">view.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/workspace/window.h" data-parent="include/workspace" style="display:none;">
<td style="text-align:left;" data-sort="b.window.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="include/workspace/window.h/">window.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/workspace/window_manager.h" data-parent="include/workspace" style="display:none;">
<td style="text-align:left;" data-sort="b.window_manager.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="include/workspace/window_manager.h/">window_manager.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/workspace/workspace.h" data-parent="include/workspace" style="display:none;">
<td style="text-align:left;" data-sort="b.workspace.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="include/workspace/workspace.h/">workspace.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="include/capi.h" data-parent="include" style="display:none;">
<td style="text-align:left;" data-sort="b.capi.h"><span class="twemoji"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8zm4 18H6V4h7v5h5z"/></svg></span> <a href="include/capi.h/">capi.h</a></td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;">0</td>
<td style="text-align:right;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
</tbody>
<tfoot>
<tr id="summary.include/graphics" data-parent="include/graphics", style="display:none;">
<td style="text-align:left;font-weight:bold;">Summary</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="summary.include/kernel" data-parent="include/kernel", style="display:none;">
<td style="text-align:left;font-weight:bold;">Summary</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="summary.include/workspace" data-parent="include/workspace", style="display:none;">
<td style="text-align:left;font-weight:bold;">Summary</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="summary.include" data-parent="include", style="display:none;">
<td style="text-align:left;font-weight:bold;">Summary</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
<tr id="summary." data-parent="">
<td style="text-align:left;font-weight:bold;">Summary</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;">0</td>
<td style="text-align:right;font-weight:bold;box-shadow: -8px 0 0 0 #4cae4fdd inset;">100.0%</td>
</tr>
</tfoot>
</table>


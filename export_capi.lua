local sprite = app.activeSprite

-- Check constraints
if sprite == nil then
  app.alert("No Sprite...")
  return
end
if sprite.colorMode ~= ColorMode.INDEXED then
  app.alert("Sprite needs to be indexed")
  return
end

local function exportFrame(frm)
	if frm == nil then
		frm = 1
	end

	local img = Image(sprite.spec)
	img:drawSprite(sprite, frm)
    
    binWidth = string.pack("<H", sprite.width)
    binHeight = string.pack("<H", sprite.height)
    io.write(binWidth)
    io.write(binHeight)
	for y = 0,sprite.height-1 do
		for x = 0, sprite.width-1 do
            pixel = img:getPixel(x, y)
            binPixel = string.pack("<B", pixel)
			io.write(binPixel);
		end
	end
end


local dlg = Dialog()
dlg:file{ id="exportFile",
          label="File",
          title="Capi Pixmap Export",
          open=false,
          save=true,
        --filename= p .. fn .. "pip",
          filetypes={"txt", "pip" }}
dlg:button{ id="ok", text="OK" }
dlg:button{ id="cancel", text="Cancel" }
dlg:show()
local data = dlg.data
if data.ok then
	local f = io.open(data.exportFile, "w")
	io.output(f)
	exportFrame(app.activeFrame)
	io.close(f)
end

del .\Output\Include\*.* /q
del .\Output\Include\Base\*.* /q
del .\Output\Include\Canvas\*.* /q
del .\Output\Include\Elements\*.* /q
del .\Output\Include\View\*.* /q
del .\Output\Include\Painter\*.* /q
del .\Output\Include\Resource\*.* /q
del .\Output\Include\Tools\*.* /q

md .\Output
md .\Output\Include
md .\Output\Include\Base
md .\Output\Include\Canvas
md .\Output\Include\Elements
md .\Output\Include\View
md .\Output\Include\Painter
md .\Output\Include\Resource
md .\Output\Include\Tools

copy .\ODL_Include.h .\Output\Include\

copy .\Base\*.h .\Output\Include\Base\
copy .\Canvas\*.h .\Output\Include\Canvas\
copy .\Elements\*.h .\Output\Include\Elements\
copy .\View\*.h .\Output\Include\View\
copy .\Painter\*.h .\Output\Include\Painter\
copy .\Resource\*.h .\Output\Include\Resource\
copy .\Tools\*.h .\Output\Include\Tools\
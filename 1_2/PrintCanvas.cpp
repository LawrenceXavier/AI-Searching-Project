#include "PrintCanvas.h"

int lenNum(pcoor val) {
	if (val == 0) return 1;
	int res = 0;
	while (val != 0) {
		++res;
		val /= 10;
	}
	return res;
}

void PrintCanvas::findLimit() {
	min_x = min_y = 1E5;
	max_x = max_y = 0;
	for (int i = 0; i < allObj->L->N; ++i) {
		min_x = min(min_x, max(allObj->getPoint(i).x-2, (pcoor)0));
		min_y = min(min_y, max(allObj->getPoint(i).y-2, (pcoor)0));
		max_x = max(max_x, min(allObj->getPoint(i).x+2, (pcoor)1E5));
		max_y = max(max_y, min(allObj->getPoint(i).y+2, (pcoor)1E5));
	}
	delta = max(max_x-min_x, max_y-min_y);
}

TPoint PrintCanvas::convert(const TPoint &A) {
	TPoint B = A-TPoint(min_x, min_y);
	B.x = B.x*maxPixel/delta;
	B.y = B.y*maxPixel/delta;
	
	B.y = maxPixel-B.y;

	B.x += wText;
	return B;
}

void PrintCanvas::drawObstacles() {
	for (int i = 0; i < allObj->N; ++i) {
		fprintf(fhtml, "\t\t// Draw %d-th polygon\n", i+1);
		fprintf(fhtml, "\t\tctx.beginPath();\n");
		
		TPoint cur = allObj->getPoint(allObj->O[i]->P[0]);
		cur = convert(cur);
		fprintf(fhtml, "\t\tctx.moveTo(%lld,%lld);\n", cur.x, cur.y);
		for (int j = 1, sz = allObj->O[i]->N; j <= sz; ++j) {
			cur = allObj->getPoint(allObj->O[i]->P[j%sz]);
			cur = convert(cur);
			fprintf(fhtml, "\t\tctx.lineTo(%lld,%lld);\n", cur.x, cur.y);
		}
		fprintf(fhtml, "\t\tctx.fillStyle = \"#333\";\n");
		fprintf(fhtml, "\t\tctx.fill();\n");	
		fprintf(fhtml, "\t\tctx.closePath();\n");
		fprintf(fhtml, "\t\tctx.stroke();\n");
	}
}

void PrintCanvas::drawSG() {
	TPoint cur;
	cur = allObj->getPoint(allObj->S);
	cur = convert(cur);
	fprintf(fhtml, "\t\t// Draw S\n");
	fprintf(fhtml, "\t\tctx.beginPath();\n");
	fprintf(fhtml, "\t\tctx.arc(%lld, %lld, 5, 0, 2*Math.PI);\n", cur.x, cur.y);
	fprintf(fhtml, "\t\tctx.fillStyle = \"Blue\";\n");
	fprintf(fhtml, "\t\tctx.fill();\n");
	fprintf(fhtml, "\t\tctx.closePath();\n");
	cur = allObj->getPoint(allObj->G);
	cur = convert(cur);
	fprintf(fhtml, "\t\t// Draw S\n");
	fprintf(fhtml, "\t\tctx.beginPath();\n");
	fprintf(fhtml, "\t\tctx.arc(%lld, %lld, 5, 0, 2*Math.PI);\n", cur.x, cur.y);
	fprintf(fhtml, "\t\tctx.fillStyle = \"Green\";\n");
	fprintf(fhtml, "\t\tctx.fill();\n");
	fprintf(fhtml, "\t\tctx.closePath();\n");
}

PrintCanvas::PrintCanvas(const char* FILE_NAME, AllObject* All_Obj) {
	allObj = All_Obj;		
	findLimit();
	
	fhtml = fopen(FILE_NAME, "w");
	fprintf(fhtml, "<!DOCTYPE HTML>\n");
	fprintf(fhtml, "<html>\n");
	fprintf(fhtml, "<head>\n");
	fprintf(fhtml, "\t<title> Drawing path </title>\n");
	fprintf(fhtml, "</head>\n");
	fprintf(fhtml, "<body>\n");
	fprintf(fhtml, "\t<canvas id=\"myCanvas\" width=\"%lld\" height=\"%lld\" style=\"border:1px solid #000000;\">\n", maxPixel+wText, maxPixel+hText);
	fprintf(fhtml, "\t</canvas>\n");
	fprintf(fhtml, "\t<script>\n");
	fprintf(fhtml, "\t\tvar canvas = document.getElementById(\"myCanvas\");\n");
	fprintf(fhtml, "\t\tvar ctx = canvas.getContext(\"2d\");\n");
	fprintf(fhtml, "\t\tctx.beginPath();\n");
	fprintf(fhtml, "\t\tctx.rect(%lld, 0, %lld, %lld);\n", wText, maxPixel, maxPixel);
	fprintf(fhtml, "\t\tctx.stroke();\n");
	fprintf(fhtml, "\t\tctx.closePath();\n");

	fprintf(fhtml, "\t\tctx.font = \"%lldpx Arial\";\n", szText);
	fprintf(fhtml, "\t\tctx.fillText(\"%lld\", %lld, %lld);\n", min_x, wText, maxPixel+szText);
	fprintf(fhtml, "\t\tctx.fillText(\"%lld\", %lld, %lld);\n", min_x+delta, maxPixel+wText-szText*lenNum(max_x)+szText/2, maxPixel+szText);
	fprintf(fhtml, "\t\tctx.fillText(\"%lld\", %lld, %lld);\n", min_y, wText-szText*lenNum(min_y), maxPixel);
	fprintf(fhtml, "\t\tctx.fillText(\"%lld\", %lld, %lld);\n", min_x+delta, wText-szText*lenNum(max_y), szText);
	drawObstacles();
	drawSG();
}


void PrintCanvas::printPath(std::vector<TPoint> path) {
	fprintf(fhtml, "\t\tvar cnt = 0;\n");
	fprintf(fhtml, "\t\tvar id = setInterval(drawPath, %.2lf);\n", 10000.0/path.size());
	fprintf(fhtml, "\t\tvar pointList = [");
	for (int i = 0, sz = path.size(); i < sz; ++i) {
		TPoint cur = convert(path[i]);
		fprintf(fhtml, " %lld, %lld", cur.x, cur.y);
		if (i+1 < sz)
			fprintf(fhtml, ",");
	}
	fprintf(fhtml, "];\n");
	
	fprintf(fhtml, "\t\tfunction drawPath() {\n");
	fprintf(fhtml, "\t\t\tcnt = cnt+1;\n");
	fprintf(fhtml, "\t\t\tif (cnt == 1) {\n");
	fprintf(fhtml, "\t\t\t\tctx.beginPath();\n");
	fprintf(fhtml, "\t\t\t\tctx.strokeStyle = \"#FF0000\";\n");
	fprintf(fhtml, "\t\t\t\tctx.moveTo(pointList[0], pointList[1]);\n");
	fprintf(fhtml, "\t\t\t}\n");

	fprintf(fhtml, "\t\t\tif (cnt == pointList.length) {\n");
	fprintf(fhtml, "\t\t\t\tclearInterval(id);\n");
	fprintf(fhtml, "\t\t\t\tctx.closePath();\n");
	fprintf(fhtml, "\t\t\t}\n");
	fprintf(fhtml, "\t\t\telse {\n");
	fprintf(fhtml, "\t\t\t\tctx.lineTo(pointList[2*cnt], pointList[2*cnt+1]);\n");
	fprintf(fhtml, "\t\t\t\tctx.stroke();\n");
	fprintf(fhtml, "\t\t\t}\n");
	fprintf(fhtml, "\t\t}\n");
}

PrintCanvas::~PrintCanvas() {
	fprintf(fhtml, "\t</script>\n");
	fprintf(fhtml, "</body>\n");
	fprintf(fhtml, "</html>\n");
	fclose(fhtml);
}

#ifndef PRINT_CANVAS_INCLUDED
#define PRINT_CANVAS_INCLUDED

#include "AllObject.h"
#include <cstdio>
#include <vector>

const pcoor maxPixel = 1200;

template<typename T> T min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> T max(const T &x, const T &y) { return x > y ? x : y; }

class PrintCanvas {
private:
	AllObject* allObj;
	pcoor min_x, min_y, max_x, max_y, delta;
	FILE* fhtml;
public:	
	void findLimit() {
		min_x = min_y = 1E5;
		max_x = max_y = 0;
		for (int i = 0; i < allObj->L->N; ++i) {
			min_x = min(min_x, allObj->getPoint(i).x);
			min_y = min(min_y, allObj->getPoint(i).y);
			max_x = max(max_x, allObj->getPoint(i).x);
			max_y = max(max_y, allObj->getPoint(i).y);
		}
		delta = max(max_x-min_x, max_y-min_y);
	}

	TPoint convert(const TPoint &A) {
		TPoint B = A-TPoint(min_x, min_y);
		B.x = B.x*maxPixel/delta;
		B.y = B.y*maxPixel/delta;
		
		B.y = maxPixel-B.y;
		return B;
	}
	
	void drawObstacles() {
		for (int i = 0; i < allObj->N; ++i) {
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

	PrintCanvas(const char* FILE_NAME, AllObject* All_Obj) {
		allObj = All_Obj;		
		findLimit();
		
		fhtml = fopen(FILE_NAME, "w");
		fprintf(fhtml, "<!DOCTYPE HTML>\n");
		fprintf(fhtml, "<html>\n");
		fprintf(fhtml, "<head>\n");
		fprintf(fhtml, "\t<title> Drawing path </title>\n");
		fprintf(fhtml, "</head>\n");
		fprintf(fhtml, "<body>\n");
		fprintf(fhtml, "\t<canvas id=\"myCanvas\" width=\"%lld\" height=\"%lld\" style=\"border:1px solid #000000;\">\n", maxPixel, maxPixel);
		fprintf(fhtml, "\t</canvas>");
		fprintf(fhtml, "\t<script>\n");
		fprintf(fhtml, "\t\tvar canvas = document.getElementById(\"myCanvas\");\n");
		fprintf(fhtml, "\t\tvar ctx = canvas.getContext(\"2d\");\n");
		drawObstacles();
	}

	

	void printPath(std::vector<TPoint> path) {
		fprintf(fhtml, "\t\tvar cnt = 0;\n");
		fprintf(fhtml, "\t\tvar id = setInterval(drawPath, 1000);\n");
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

		fprintf(fhtml, "\t\t\tif (cnt == pointList.length) \n");
		fprintf(fhtml, "\t\t\t\tclearInterval(id);\n");
		fprintf(fhtml, "\t\t\telse {\n");
		fprintf(fhtml, "\t\t\t\tctx.lineTo(pointList[2*cnt], pointList[2*cnt+1]);\n");
		fprintf(fhtml, "\t\t\t\tctx.stroke();\n");
		fprintf(fhtml, "\t\t\t}\n");
		fprintf(fhtml, "\t\t}\n");
	}

	~PrintCanvas() {
		fprintf(fhtml, "\t</script>\n");
		fprintf(fhtml, "</body>\n");
		fclose(fhtml);
	}
};

#endif

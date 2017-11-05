#pragma once
//GDAL

#include <gdal/gdal.h>
#include <gdal/gdal_priv.h>
#include <gdal/ogrsf_frmts.h>

class WorldMapCoordinates {//класа карти в форматі тіфф , включає в себе геодані  з карти і функції доступу до них 
private:	int widthMap, heightMap;
			float topLeftX, topLeftY, topRightX, bottomLeftY;
			float widthPixel, heightPixel;
			double adfGeoTransform[6];
			GDALDataset *poDataset;
			float coordinateX;
			float coordinateY;
			
public:
	WorldMapCoordinates() {
	}
	WorldMapCoordinates(char patch[]) {
		GDALAllRegister();
		poDataset = (GDALDataset*)GDALOpen(patch, GA_ReadOnly);

		if (poDataset->GetGeoTransform(adfGeoTransform) == CE_None)
		{
			topLeftX = adfGeoTransform[0];
			topLeftY = adfGeoTransform[3];
			heightPixel = adfGeoTransform[5];
			widthPixel = adfGeoTransform[1];

			widthMap = GDALGetRasterXSize(poDataset);
			heightMap = GDALGetRasterYSize(poDataset);
			topRightX = topLeftX + adfGeoTransform[1] * widthMap;
			bottomLeftY = topLeftY + adfGeoTransform[5] * heightMap;
			convertGlobalPosToLocal();
			std::cout << " Coordinate LeftX " << topLeftX << " , " << topLeftY << " RrghtTopX " << topRightX << std::endl << " Lenght pixel " << widthPixel << "," << heightPixel << std::endl << "Data size: " << widthMap << " " << heightMap << std::endl;
		}
	}
	int getWidthMap()
	{
		return widthMap;
	}
	int getHeightMap()
	{
		return heightMap;
	}
   void convertGlobalPosToLocal() {
	   coordinateX = (topLeftX - 692332) / (topRightX - topLeftX);
	   coordinateY = (210567 - topLeftY) / (bottomLeftY - topLeftY);
		
	}

   float getCoordinateX()
   {
	   return coordinateX;
   }
   float getCoordinateY()
   {
	   return coordinateY;
   }
   float getTopLeftX()
   {
	   return topLeftX;
   }
   float getBottomLeftY()
   {
	   return bottomLeftY;
   }
   float getTopRightX()
   {
	   return topRightX;
   }
   float getTopLeftY()
   {
	   return topLeftY;
   }
   float getWidthPixel()
   {
	   return widthPixel;
   }
};

